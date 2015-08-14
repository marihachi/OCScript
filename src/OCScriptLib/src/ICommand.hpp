#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	// コマンドのアクセスメソッド用のイベント引数です。
	class AccessEventArgs
	{
	private:
		bool _IsCancelNextCommand;
	public:

		// コンストラクタ
		AccessEventArgs()
		{
			_IsCancelNextCommand = false;
		}
		
		// 次のコマンドへの遷移をキャンセルします。
		void CancelNextCommand()
		{
			_IsCancelNextCommand = true;
		}

		// IsCancelNextCommand の値を取得します。
		bool GetIsCancelNextCommand()
		{
			return _IsCancelNextCommand;
		}
	};

	// スクリプト命令のインターフェイスクラスです。
	class ICommand
	{
	public:
		virtual ~ICommand() {}

		// 命令名を取得します。
		virtual string GetCommandName() = 0;

		// コマンドにアクセスされた時に呼び出されます。
		virtual void Access(AccessEventArgs *e, vector<string> params) = 0;
		
		// 更新前のタイミングに呼び出されます。
		virtual void PreUpdate();
		
		// 更新のタイミングに呼び出されます。
		virtual void Update();
	};
}
