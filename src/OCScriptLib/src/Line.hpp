#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	// スクリプト文を表します。
	class Line
	{
	private:
		string _CommandName;
		vector<string> _Params;
	public:

		// コンストラクタ
		// 引数: 命令名, パラメータ
		Line(string commandName, vector<string> params)
		{
			_CommandName = commandName;
			_Params = params;
		}

		// コマンド名を取得します。
		string GetCommandName()
		{
			return _CommandName;
		}
		
		// パラメータを取得します。
		vector<string> GetParams()
		{
			return _Params;
		}
	};
}
