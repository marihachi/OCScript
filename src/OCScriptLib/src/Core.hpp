#pragma once
using namespace std;

#include <iostream>
#include <vector>
#include <regex>

#include "IEventHandler.hpp"
#include "ICommand.hpp"
#include "Line.hpp"
#include "Utility.hpp"

namespace OCScript
{
	// OCScriptのコアクラスです。
	class Core
	{
	private:
		vector<ICommand*> _Commands;
		bool _IsEndOfScript;
		vector<Line> _ScriptStorage;
		unsigned int _CurrentLineIndex;
	public:

		// コンストラクタ
		Core()
		{
			_IsEndOfScript = true;
			_CurrentLineIndex = 0;
		}

		// コマンドを登録します。
		// 引数: ICommandExecutableを実装したコマンドのクラス
		// ※例外が発生する可能性のあるメソッドです
		void AddCommand(ICommand *command)
		{
			if (regex_match(command->GetCommandName(), wregex(L"[ \t]*$")))
				throw exception("コマンド名が不正です。");

			_Commands.push_back(command);
		}

		// スクリプトを実行し終えたかどうかを示す値を取得します。
		bool IsEndOfScript()
		{
			return _IsEndOfScript;
		}

		// 次に実行される行を設定します。
		// 引数: 行の0から始まるインデックス
		void SetCurrentLineIndex(unsigned int lineIndex)
		{
			_CurrentLineIndex = lineIndex;
		}

		// スクリプト文を ScriptStorage に一括読み込みします。
		// 引数: 行区切り文字列のベクタ
		// ※例外が発生する可能性のあるメソッドです
		void LoadScript(const vector<wstring> scriptLines)
		{
			vector<Line> lines;

			int lineIndex = 1;
			for (auto scriptLine : scriptLines)
			{
				wsmatch m1, m2;

				// 空行でない
				if (!regex_match(scriptLine, wregex(L"^[ \t]*$")))
				{
					m1 = wsmatch();

					// 構文にマッチする
					if (regex_match(scriptLine, m1, wregex(L"^[ \t]*([a-zA-Z0-9._-]+)[ \t]*\\((.+)\\)[ \t]*;[ \t]*$")))
					{
						wstring commandName = m1[1];
						wstring paramsStr = m1[2];

						vector<wstring> paramsSourceVec = Utility::StrSplit(paramsStr, ',');
						vector<wstring> paramsDestVec;
						int paramIndex = 1;
						for (auto paramToken : paramsSourceVec)
						{
							wstring content;
							m1 = wsmatch();
							m2 = wsmatch();

							// クォート付きの引数である
							if (regex_match(paramToken, m1, wregex(L"^[ \t]*\"(.*)\"[ \t]*$")) || regex_match(paramToken, m2, wregex(L"^[ \t]*\'(.*)\'[ \t]*$")))
							{
								if (!m1.empty())
									content = m1[1];
								else if (!m2.empty())
									content = m2[1];
								else
									throw exception(("システムエラーが発生しました。マッチ結果が矛盾しています。(行: " + to_string(lineIndex) + ")").c_str());
							}
							else
							{
								m1 = wsmatch();
								if (!regex_match(paramToken, m1, wregex(L"^[ \t]*([^ \t]*)[ \t]*$")))
									throw exception(("引数の解析時にエラーが発生しました。(行: " + to_string(lineIndex) + ", 引数番号: " + to_string(paramIndex) + ")").c_str());

								content = m1[1];
							}
							paramsDestVec.push_back(content);
							paramIndex++;
						}
						lines.push_back(Line(commandName, paramsDestVec));
					}
					else
						throw exception(("構文エラーが発生しました。(行: " + to_string(lineIndex) + ")").c_str());
				}
				lineIndex++;
			}
			_ScriptStorage = vector<Line>(lines);
			_IsEndOfScript = (_CurrentLineIndex > _ScriptStorage.size() - 1);
		}
		// スクリプト文を ScriptStorage に一括読み込みします。
		// 引数: スクリプトの文字列
		// ※例外が発生する可能性のあるメソッドです
		void LoadScript(const wstring scriptText)
		{
			vector<wstring> scriptLines = Utility::StrSplit(scriptText, L'\n');
			LoadScript(scriptLines);
		}

		// 実行の対象となっているスクリプト文を実行します。
		// ※例外が発生する可能性のあるメソッドです
		void ExecuteCurrentLine()
		{
			if (_ScriptStorage.empty())
				throw exception("ScriptStorageの中身が空でした。");

			if (_CurrentLineIndex > _ScriptStorage.size() - 1)
				throw exception("スクリプトは最後まで実行されています。");

			auto line = _ScriptStorage[_CurrentLineIndex];

			bool isFoundCommand = false;
			for (auto command : _Commands)
			{
				if (line.GetCommandName() == command->GetCommandName())
				{
					isFoundCommand = true;
					AccessEventArgs accessEventArgs;
					command->Access(&accessEventArgs, line.GetParams());
					if (!accessEventArgs.GetIsCancelNextCommand())
						_CurrentLineIndex++;
				}
			}

			if (!isFoundCommand)
				throw exception("未定義のスクリプト文が呼び出されました。");

			_IsEndOfScript = (_CurrentLineIndex > _ScriptStorage.size() - 1);
		}
	};
}
