#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	// スクリプト文を表します。
	class Line
	{
	private:
		wstring _CommandName;
		vector<wstring> _Params;
	public:
		// コンストラクタ
		// 引数: 命令名, パラメータ
		Line(wstring commandName, vector<wstring> params)
		{
			_CommandName = commandName;
			_Params = params;
		}

		// コマンド名を取得します。
		wstring GetCommandName()
		{
			return _CommandName;
		}
		
		// パラメータを取得します。
		vector<wstring> GetParams()
		{
			return _Params;
		}
	};
}
