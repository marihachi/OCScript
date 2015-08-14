#include <tchar.h>
#include <fstream>
#include <iostream>

#include "../../OCScriptLib/src/OCScript.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		ifstream ifs(argv[1]);
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
			osc.LoadScript(scriptVec);
		}
		catch (exception ex)
		{
			cerr << ex.what() << endl;
			return -1;
		}
	}
	return 0;
}
