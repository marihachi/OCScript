#include <fstream>
#include <iostream>
#include <tchar.h>

#include "../../OCScriptLib/src/OCScript.hpp"

class Test : public OCScript::ICommand
{
public:
	string GetCommandName()
	{
		return "Test";
	}

	void Access(OCScript::AccessEventArgs *e, vector<string> params)
	{
		cout << "Testが呼び出されました" << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		OCScript::Core osc;

		Test test;

		ifstream ifs(argv[1]);
		if (ifs.fail())
		{
			cerr << "読み込みに失敗しました" << endl;
			return -1;
		}
		char str[256];
		vector<string> rawLines;
		while (ifs.getline(str, sizeof(str)))
			rawLines.push_back(str);

		try
		{
			// コマンド登録
			osc.AddCommand(&test);

			// スクリプトの読み込み
			osc.LoadScript(rawLines);
		}
		catch (exception ex)
		{
			cerr << ex.what() << endl;
			return -1;
		}
		// 1行だけ実行
		osc.ExecuteCurrentLine();
	}
	return 0;
}
