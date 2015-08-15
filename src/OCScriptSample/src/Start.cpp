#include <fstream>
#include <iostream>
#include <tchar.h>

#include "../../OCScriptLib/src/OCScript.hpp"

class Test : public OCScript::ICommand
{
public:
	wstring GetCommandName()
	{
		return L"Test";
	}

	void Access(OCScript::AccessEventArgs *e, vector<wstring> params)
	{
		wcout << L"Testが呼び出されました" << endl;
		wcout << L"引数一覧:" << endl;
		for (auto item : params)
			wcout << L"- " + item << endl;
	}
};

int wmain(int argc, wchar_t* argv[])
{
	_wsetlocale(LC_ALL, L"");

	if (argc == 2)
	{
		OCScript::Core osc;

		Test test;

		vector<wstring> rawLines;

		FILE* stream;
		int openError = _wfopen_s(&stream, argv[1], L"r, ccs=UTF-8");
		if (openError == 0 && stream)
		{
			while (feof(stream) == 0)
			{
				wchar_t str[256];
				fgetws(str, sizeof(str), stream);
				if (ferror(stream) != 0)
				{
					fclose(stream);
					wcerr << L"読み込みに失敗しました" << endl;
					return -1;
				}
				rawLines.push_back(str);
			}
			fclose(stream);
		}
		else
		{
			wcerr << L"ファイルオープンに失敗しました" << endl;
			return -1;
		}

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
