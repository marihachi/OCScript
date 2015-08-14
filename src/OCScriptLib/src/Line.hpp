#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	// �X�N���v�g����\���܂��B
	class Line
	{
	private:
		string _CommandName;
		vector<string> _Params;
	public:

		// �R���X�g���N�^
		// ����: ���ߖ�, �p�����[�^
		Line(string commandName, vector<string> params)
		{
			_CommandName = commandName;
			_Params = params;
		}

		// �R�}���h�����擾���܂��B
		string GetCommandName()
		{
			return _CommandName;
		}
		
		// �p�����[�^���擾���܂��B
		vector<string> GetParams()
		{
			return _Params;
		}
	};
}