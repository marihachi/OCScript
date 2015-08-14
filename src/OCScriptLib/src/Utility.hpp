#pragma once
using namespace std;

#include <vector>
#include <sstream>

namespace OCScript
{
	// �֗��ȋ@�\���܂Ƃ߂��N���X�ł��B
	class Utility
	{
	public:
		// ��؂蕶���ɂ�蕶������X�v���b�g���܂��B
		// ����: �\�[�X������, ��؂蕶��
		static vector<string> StrSplit(const string &src, char delimiter)
		{
			stringstream ss(src);
			vector<string> items;
			string item;

			while (getline(ss, item, delimiter))
				items.push_back(item);

			return items;
		}

		// �������u�����ĐV����������Ƃ��ĕԂ��܂��B
		// ����: �\�[�X������, �Ώۂ̕�����, �u����̕�����
		static string StrReplace(const string src, const string oldVal, const string newVal)
		{
			auto temp = src;
			string::size_type pos(temp.find(oldVal));

			while (pos != string::npos)
			{
				temp.replace(pos, oldVal.length(), newVal);
				pos = temp.find(oldVal, pos + newVal.length());
			}

			return temp;
		}
	};
}
