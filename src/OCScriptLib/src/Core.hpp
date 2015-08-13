#pragma once
using namespace std;

#include <vector>
#include <regex>

#include "ICommand.hpp"
#include "Line.hpp"
#include "Utility.hpp"

namespace OCScript
{
	// �X�N���v�g����舵���R�A�N���X�ł��B
	class Core
	{
	private:
		vector<ICommand*> _Commands;
		vector<Line> _Lines;
		int _LineIndex;
	public:
		// ���߂�ǉ����܂��B
		// ����: ICommand�������������߂̃N���X
		void AddCommand(ICommand *command)
		{
			_Commands.push_back(command);
		}

		// �X�N���v�g��ǂݍ��݂܂��B
		// ����: �s��؂蕶����̃x�N�^
		// ����O����������\���̂��郁�\�b�h�ł�
		void LoadScript(const vector<string> scriptLines)
		{
			int lineIndex = 1;
			vector<Line> lines;

			for (auto scriptLine : scriptLines)
			{
				smatch m1, m2;

				// ��s�ł͂Ȃ��ꍇ
				if (!regex_match(scriptLine, regex("^[ \t]*$")))
				{
					m1 = smatch();
					// ���ߍ\���Ƀ}�b�`����ꍇ
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

							// �N�H�[�g�t���̈����̏ꍇ
							if (regex_match(paramToken, m1, regex("^[ \t]*\"(.*)\"[ \t]*$")) || regex_match(paramToken, m2, regex("^[ \t]*\'(.*)\'[ \t]*$")))
							{
								if (!m1.empty())
									content = m1[1];
								else if (!m2.empty())
									content = m2[1];
								else
								{
									char message[256];
									sprintf_s(message, "�V�X�e���G���[���������܂����B�}�b�`���ʂ��������Ă��܂��B(�s: %d)", lineIndex);
									throw exception(message);
								}
							}
							// �ʏ�̈����̏ꍇ
							else
							{
								m1 = smatch();
								if (!regex_match(paramToken, m1, regex("^[ \t]*([a-zA-Z0-9._-]*)[ \t]*$")))
								{
									char message[256];
									sprintf_s(message, "�����̉�͎��ɃG���[���������܂����B(�s: %d, �����ԍ�: %d)", lineIndex, paramIndex);
									throw exception(message);
								}
								content = m1[1];
							}
							paramsDestVec.push_back(content);
							paramIndex++;
						}
						lines.push_back(Line(commandName, paramsDestVec));
					}
					// ���ߍ\���Ƀ}�b�`���Ȃ��ꍇ
					else
					{
						char message[256];
						sprintf_s(message, "�\���G���[���������܂����B(�s: %d)", lineIndex);
						throw exception(message);
					}
				}
				lineIndex++;
			}
			_Lines = vector<Line>(lines);
		}
		// �X�N���v�g��ǂݍ��݂܂��B
		// ����: �X�N���v�g�̕�����
		// ����O����������\���̂��郁�\�b�h�ł�
		void LoadScript(const string scriptText)
		{
			vector<string> scriptLines = Utility::StrSplit(scriptText, '\n');
			LoadScript(scriptLines);
		}

		// ���s���s��ύX���܂��B
		// ����: �s��0����n�܂�C���f�b�N�X
		void SetLineIndex(int lineIndex)
		{
			_LineIndex = lineIndex;
		}
	};
}