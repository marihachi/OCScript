#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	/* スクリプト命令のインターフェイスクラスです。 */
	class ICommand
	{
	public:
		virtual ~ICommand() {}
	public:
		// 命令名を取得します。
		virtual string GetCommandName() = 0;
		// コマンドにアクセスされた時に呼び出されます。
		virtual void Access(vector<string> params) = 0;
		// 更新するタイミングに呼び出されます。
		virtual void Update() = 0;
		// 描画するタイミングに呼び出されます。
		virtual void Draw() = 0;
	};
}