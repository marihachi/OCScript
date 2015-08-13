#pragma once
using namespace std;

#include <vector>
#include <regex>

#include "ICommand.hpp"
#include "Line.hpp"
#include "Utility.hpp"

namespace OCScript
{
	// スクリプトを取り扱うコアクラスです。
	class Core
	{
	private:
		vector<ICommand*> _Commands;
		vector<Line> _Lines;
		int _LineIndex;
	public:
		// 命令を追加します。
		// 引数: ICommandを実装した命令のクラス
		void AddCommand(ICommand *command)
		{
			_Commands.push_back(command);
		}

		// スクリプトを読み込みます。
		// 引数: 行区切り文字列のベクタ
		// ※例外が発生する可能性のあるメソッドです
		void LoadScript(const vector<string> scriptLines)
		{
			int lineIndex = 1;
			vector<Line> lines;

			for (auto scriptLine : scriptLines)
			{
				smatch m1, m2;

				// 空行ではない場合
				if (!regex_match(scriptLine, regex("^[ \t]*$")))
				{
					m1 = smatch();
					// 命令構文にマッチする場合
					if (regex_match(scriptLine, m1, regex("^[ \t]*([a-zA-Z0-9._-]+)\\((.+)\\);[ \t]*$")))
					{
						string commandName = m1[1];
						string paramsStr = m1[2];

						vector<string> paramsSourceVec = Utility::StrSplit(paramsStr, ',');
						vector<string> paramsDestVec;
						int paramIndex = 1;
						for (auto paramToken : paramsSourceVec)
						{
							string content;
							m1 = smatch();
							m2 = smatch();

							// クォート付きの引数の場合
							if (regex_match(paramToken, m1, regex("^[ \t]*\"(.*)\"[ \t]*$")) || regex_match(paramToken, m2, regex("^[ \t]*\'(.*)\'[ \t]*$")))
							{
								if (!m1.empty())
									content = m1[1];
								else if (!m2.empty())
									content = m2[1];
								else
								{
									char message[256];
									sprintf_s(message, "システムエラーが発生しました。マッチ結果が矛盾しています。(行: %d)", lineIndex);
									throw exception(message);
								}
							}
							// 通常の引数の場合
							else
							{
								m1 = smatch();
								if (!regex_match(paramToken, m1, regex("^[ \t]*([a-zA-Z0-9._-]*)[ \t]*$")))
								{
									char message[256];
									sprintf_s(message, "引数の解析時にエラーが発生しました。(行: %d, 引数番号: %d)", lineIndex, paramIndex);
									throw exception(message);
								}
								content = m1[1];
							}
							paramsDestVec.push_back(content);
							paramIndex++;
						}
						lines.push_back(Line(commandName, paramsDestVec));
					}
					// 命令構文にマッチしない場合
					else
					{
						char message[256];
						sprintf_s(message, "構文エラーが発生しました。(行: %d)", lineIndex);
						throw exception(message);
					}
				}
				lineIndex++;
			}
			_Lines = vector<Line>(lines);
		}
		// スクリプトを読み込みます。
		// 引数: スクリプトの文字列
		// ※例外が発生する可能性のあるメソッドです
		void LoadScript(const string scriptText)
		{
			vector<string> scriptLines = Utility::StrSplit(scriptText, '\n');
			LoadScript(scriptLines);
		}

		// 実行中行を変更します。
		// 引数: 行の0から始まるインデックス
		void SetLineIndex(int lineIndex)
		{
			_LineIndex = lineIndex;
		}
	};
}