#pragma once

namespace OCScript
{
	// �C�x���g�n���h����\���܂��B
	class IEventHandler
	{
	public:
		virtual ~IEventHandler() {}

		// ���s�Ώۂ̃��\�b�h��\���܂��B
		virtual void Target() = 0;
	};
}
