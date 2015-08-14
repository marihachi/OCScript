#pragma once

namespace OCScript
{
	// イベントハンドラを表します。
	class IEventHandler
	{
	private:
		virtual ~IEventHandler() {}

		// 実行対象のメソッドを表します。
		virtual void Target() = 0;
	};
}
