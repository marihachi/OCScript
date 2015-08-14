#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	// コマンドのアクセスメソッド用のイベントです。
	class AccessEvent
	{
	private:
		bool _IsCancelNextCommand;
	public:

		// コンストラクタ
		AccessEvent()
		{
			_IsCancelNextCommand = false;
		}
		
		// 次のコマンドへの遷移をキャンセルします。
		void CancelNextCommand()
		{
			_IsCancelNextCommand = true;
		}
	};

	// スクリプト命令のインターフェイスクラスです。
	class ICommandExecutable
	{
	public:
		virtual ~ICommandExecutable() {}

		// 命令名を取得します。
		virtual string GetCommandName() = 0;

		// コマンドにアクセスされた時に呼び出されます。
		virtual void Access(AccessEvent e, vector<string> params) = 0;
		
		// 更新前のタイミングに呼び出されます。
		virtual void PreUpdate();
		
		// 更新のタイミングに呼び出されます。
		virtual void Update();
	};
}