#include <tchar.h>
#include <fstream>
#include <iostream>

#include "../../OCScriptLib/src/OCScript.hpp"

class Test : public OCScript::ICommand
{
public:
	virtual string GetCommandName()
	{
		return "Test";
	}

	virtual void Access(OCScript::AccessEventArgs *e, vector<string> params)
	{

	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	//if (argc == 2)
	//{
		//ifstream ifs(argv[1]);
		ifstream ifs("D:\\git\\OCScript\\src\\Debug\\script.txt");
		char str[256];
		vector<string> scriptVec;
		OCScript::Core osc;

		if (ifs.fail())
		{
			cerr << "読み込みに失敗しました" << endl;
			return -1;
		}
		while (ifs.getline(str, 255))
			scriptVec.push_back(str);

		try
		{
			// コマンド登録
			osc.AddCommand(&Test());

			// スクリプトの読み込み
			osc.LoadScript(scriptVec);

			osc.ExecuteCurrentLine();
		}
		catch (exception ex)
		{
			cerr << ex.what() << endl;
			return -1;
		}
	//}
	return 0;
}
