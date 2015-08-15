#include <fstream>
#include <iostream>

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

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		ifstream ifs(argv[1]);
		char str[256];
		vector<string> scriptVec;
		OCScript::Core osc;

		cout << "読み込みに失敗しました" << endl;

		if (ifs.fail())
		{
			cerr << "読み込みに失敗しました" << endl;
			return -1;
		}
		while (ifs.getline(str, 255))
			scriptVec.push_back(str);

		Test test;

		try
		{
			// コマンド登録
			osc.AddCommand(&test);

			// スクリプトの読み込み
			osc.LoadScript(scriptVec);

			// 1行だけ実行
			osc.ExecuteCurrentLine();
		}
		catch (exception ex)
		{
			cerr << ex.what() << endl;
			return -1;
		}
	}
	return 0;
}
