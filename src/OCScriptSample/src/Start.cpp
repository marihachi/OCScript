#include <fstream>
#include <iostream>

#include "../../OCScriptLib/src/OCScript.hpp"

class SampleCommand1 : public OCScript::ICommand
{
public: static SampleCommand1& GetInstance() { static SampleCommand1 instance; return instance; }
private: SampleCommand1() { }

public:
	wstring GetCommandName()
	{
		return L"SampleCommand1";
	}

	void Access(OCScript::AccessEventArgs *e, vector<wstring> params)
	{
		wcout << L"SampleCommand1が呼び出されました" << endl;
		wcout << L"引数一覧:" << endl;
		for (auto item : params)
			wcout << L"- " + item << endl;
	}

	void PreUpdate()
	{
		wcout << L"SampleCommand1 前更新処理" << endl;
	}

	void Update()
	{
		wcout << L"SampleCommand1 本更新処理" << endl;
	}
};

class SampleCommand2 : public OCScript::ICommand
{
public: static SampleCommand2& GetInstance() { static SampleCommand2 instance; return instance; }
private: SampleCommand2() { }

public:
	wstring GetCommandName()
	{
		return L"SampleCommand2";
	}

	void Access(OCScript::AccessEventArgs *e, vector<wstring> params)
	{
		wcout << L"SampleCommand2が呼び出されたよ！" << endl;
	}

	void PreUpdate()
	{
		wcout << L"SampleCommand2 前更新処理" << endl;
	}

	void Update()
	{
		wcout << L"SampleCommand2 本更新処理" << endl;
	}
};

int wmain(int argc, wchar_t* argv[])
{
	_wsetlocale(LC_ALL, L"");

	if (argc == 2)
	{
		OCScript::Core osc;

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
			osc.AddCommand(&SampleCommand1::GetInstance());
			osc.AddCommand(&SampleCommand2::GetInstance());

			// スクリプトの読み込み
			osc.LoadScript(rawLines);

			while (!osc.IsEndOfScript())
			{
				// 現在の行を実行
				osc.ExecuteCurrentLine();

				// 更新(描画処理や計算処理などを含む)
				osc.TriggerPreUpdate();
				osc.TriggerUpdate();
			}
		}
		catch (exception ex)
		{
			cerr << ex.what() << endl;
			return -1;
		}
	}
	return 0;
}
