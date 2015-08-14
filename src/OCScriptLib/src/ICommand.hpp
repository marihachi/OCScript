#pragma once
using namespace std;

#include <vector>

namespace OCScript
{
	// �R�}���h�̃A�N�Z�X���\�b�h�p�̃C�x���g�����ł��B
	class AccessEventArgs
	{
	private:
		bool _IsCancelNextCommand;
	public:

		// �R���X�g���N�^
		AccessEventArgs()
		{
			_IsCancelNextCommand = false;
		}
		
		// ���̃R�}���h�ւ̑J�ڂ��L�����Z�����܂��B
		void CancelNextCommand()
		{
			_IsCancelNextCommand = true;
		}

		// IsCancelNextCommand �̒l���擾���܂��B
		bool GetIsCancelNextCommand()
		{
			return _IsCancelNextCommand;
		}
	};

	// �X�N���v�g���߂̃C���^�[�t�F�C�X�N���X�ł��B
	class ICommand
	{
	public:
		virtual ~ICommand() {}

		// ���ߖ����擾���܂��B
		virtual string GetCommandName() = 0;

		// �R�}���h�ɃA�N�Z�X���ꂽ���ɌĂяo����܂��B
		virtual void Access(AccessEventArgs *e, vector<string> params) = 0;
		
		// �X�V�O�̃^�C�~���O�ɌĂяo����܂��B
		virtual void PreUpdate();
		
		// �X�V�̃^�C�~���O�ɌĂяo����܂��B
		virtual void Update();
	};
}
