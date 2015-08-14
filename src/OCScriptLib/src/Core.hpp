#pragma once
using namespace std;

#include <vector>
#include <regex>
#include "IEventHandler.hpp"
#include "ICommand.hpp"
#include "Line.hpp"
#include "Utility.hpp"

namespace OCScript
{
	// OCScript�̃R�A�N���X�ł��B
	class Core
	{
	private:
		vector<ICommand*> _Commands;

		vector<Line> _ScriptStorage;
		unsigned int _CurrentLineIndex;
	public:

		// �R�}���h��ǉ����܂��B
		// ����: ICommandExecutable�����������R�}���h�̃N���X
		void AddCommand(ICommand *command)
		{
			_Commands.push_back(command);
		}

		// ���Ɏ��s�����s��ύX���܂��B
		// ����: �s��0����n�܂�C���f�b�N�X
		void SetCurrentLineIndex(int lineIndex)
		{
			_CurrentLineIndex = lineIndex;
		}

		// �X�N���v�g���� ScriptStorage �Ɉꊇ�ǂݍ��݂��܂��B
		// ����: �s��؂蕶����̃x�N�^
		// ����O����������\���̂��郁�\�b�h�ł�
		void LoadScript(const vector<string> scriptLines)
		{
			vector<Line> lines;

			int lineIndex = 1;
			for (auto scriptLine : scriptLines)
			{
				smatch m1, m2;

				// ��s�łȂ�
				if (!regex_match(scriptLine, regex("^[ \t]*$")))
				{
					m1 = smatch();

					// �\���Ƀ}�b�`����
					if (regex_match(scriptLine, m1, regex("^[ \t]*([a-zA-Z0-9._-]+)[ \t]*\\((.+)\\)[ \t]*;[ \t]*$")))
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

							// �N�H�[�g�t���̈����ł���
							if (regex_match(paramToken, m1, regex("^[ \t]*\"(.*)\"[ \t]*$")) || regex_match(paramToken, m2, regex("^[ \t]*\'(.*)\'[ \t]*$")))
							{
								if (!m1.empty())
									content = m1[1];
								else if (!m2.empty())
									content = m2[1];
								else
									throw exception(("�V�X�e���G���[���������܂����B�}�b�`���ʂ��������Ă��܂��B(�s: " + to_string(lineIndex) + ")").c_str());
							}
							else
							{
								m1 = smatch();
								if (!regex_match(paramToken, m1, regex("^[ \t]*([^ \t]*)[ \t]*$")))
									throw exception(("�����̉�͎��ɃG���[���������܂����B(�s: " + to_string(lineIndex) + ", �����ԍ�: " + to_string(paramIndex) + ")").c_str());

								content = m1[1];
							}
							paramsDestVec.push_back(content);
							paramIndex++;
						}
						lines.push_back(Line(commandName, paramsDestVec));
					}
					else
						throw exception(("�\���G���[���������܂����B(�s: " + to_string(lineIndex) + ")").c_str());
				}
				lineIndex++;
			}
			_ScriptStorage = vector<Line>(lines);
		}

		// �X�N���v�g���� ScriptStorage �Ɉꊇ�ǂݍ��݂��܂��B
		// ����: �X�N���v�g�̕�����
		// ����O����������\���̂��郁�\�b�h�ł�
		void LoadScript(const string scriptText)
		{
			vector<string> scriptLines = Utility::StrSplit(scriptText, '\n');
			LoadScript(scriptLines);
		}

		// ���s�̑ΏۂƂȂ��Ă���X�N���v�g�������s���܂��B
		// ����O����������\���̂��郁�\�b�h�ł�
		void ExecuteCurrentLine()
		{
			if (_ScriptStorage.empty())
				throw("ScriptStorage�̒��g����ł����B");

			if (_CurrentLineIndex > _ScriptStorage.size() - 1)
				throw("�X�N���v�g�͍Ō�܂Ŏ��s����Ă��܂��B");

			auto line = _ScriptStorage[_CurrentLineIndex];

			for (auto command : _Commands)
				if (line.GetCommandName() == command->GetCommandName())
				{
					AccessEventArgs accessEventArgs;
					command->Access(&accessEventArgs, line.GetParams());
					if (!accessEventArgs.GetIsCancelNextCommand())
						_CurrentLineIndex++;
				}

			if (_CurrentLineIndex >= _ScriptStorage.size() - 1)
			{

			}
		}
	};
}
