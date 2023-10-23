#pragma once
#include <Siv3D.hpp>

namespace dss
{
	class InputState
	{
	public:
		bool leftDown = false;
		bool leftPressed = false;
		bool leftUp = false;
		bool leftLongPressed = false;

		bool rightDown = false;
		bool rightPressed = false;
		bool rightUp = false;
		bool rightLogPressed = false;

		bool upDown = false;
		bool upPressed = false;
		bool upUp = false;
		bool upLongPressed = false;

		bool downDown = false;
		bool downPressed = false;
		bool downUp = false;
		bool downLongPressed = false;

		Vec2 leftStick = Vec2::Zero();

		bool applyDown = false;
		bool applyPressed = false;
		bool applyUp = false;

		bool cancelDown = false;
		bool cancelPressed = false;
		bool cancelUp = false;

		bool pauseDown = false;
		bool pausePressed = false;
		bool pauseUp = false;
	};
}
