#pragma once
#include "InputSet.hpp"
#include "InputState.hpp"

namespace dss
{
	class InputManager
	{
	public:
		InputManager();
		void beginFrame();

		InputState inputState() const;

		void setLongPressThreshold(const uint32 ms);


	private:
		InputState m_state;
		InputSet m_inputs;

		InputSet m_keyboard;

		detail::XInput_impl m_xController = XInput(0);
		ProController m_proController;
		detail::Gamepad_impl m_gamepad = Gamepad(0);

		Optional<uint8> m_previousXLStickD4, m_previousXRStickD4;
		Optional<uint8> m_previousProLStickD4, m_previousProRStickD4;
		Optional<uint8> m_previousGamepadLStickD4, m_previousGamepadRStickD4;

		double m_longPressThreshold = 0.2;
		Stopwatch m_leftStopwatch;
		Stopwatch m_rightStopwatch;
		Stopwatch m_upStopwatch;
		Stopwatch m_downStopwatch;

		bool m_isActive;


		void updateXInput();
		void updateProCon();
		void updateGamepad();

		void updateLeft();
		void updateRight();
		void updateUp();
		void updateDown();

		void updateLeftStick();

		void updateApply();
		void updateCancel();
		void updatePause();

		void updateLeftLongPress();
		void updateRightLongPress();
		void updateUpLongPress();
		void updateDownLongPress();

		bool leftStickD4Down(const uint8 direction) const;
		bool leftStickD4Pressed(const uint8 direction) const;
		bool leftStickD4Up(const uint8 direction) const;

		Optional<uint8> proLeftStickD4(double threshold = 0.2) const;
		Optional<uint8> proRightStickD4(double threshold = 0.2) const;

		Optional<uint8> gamepadLeftStickD4(double threshold = 0.2) const;
		Optional<uint8> gamepadRightStickD4(double threshold = 0.2) const;
	};
}
