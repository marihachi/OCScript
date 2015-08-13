#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	/* �X�N���v�g���߂̃C���^�[�t�F�C�X�N���X�ł��B */
	class ICommand
	{
	public:
		virtual ~ICommand() {}
	public:
		// ���ߖ����擾���܂��B
		virtual string GetCommandName() = 0;
		// �R�}���h�ɃA�N�Z�X���ꂽ���ɌĂяo����܂��B
		virtual void Access(vector<string> params) = 0;
		// �X�V����^�C�~���O�ɌĂяo����܂��B
		virtual void Update() = 0;
		// �`�悷��^�C�~���O�ɌĂяo����܂��B
		virtual void Draw() = 0;
	};
}