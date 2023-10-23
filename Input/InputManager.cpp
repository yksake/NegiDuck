#include "InputManager.hpp"

using namespace dss;


InputManager::InputManager()
{
	// Keyboard
	{
		m_keyboard.left = { KeyLeft | KeyA };
		m_keyboard.right = { KeyRight | KeyD };
		m_keyboard.up = { KeyUp | KeyW };
		m_keyboard.down = { KeyDown | KeyS };

		m_keyboard.apply = { KeyX | KeyEnter | KeySpace };
		m_keyboard.cancel = { KeyZ | KeyShift | KeyBackspace | KeyDelete };
		m_keyboard.pause = { KeyEscape };
	}

	// Gamepads
	{
		m_xController = XInput(0);
		m_proController = ProController{ 0 };
		m_gamepad = Gamepad(0);
	}

	m_previousXLStickD4 = none;
	m_previousXRStickD4 = none;

	m_previousProLStickD4 = none;
	m_previousProRStickD4 = none;

	m_previousGamepadLStickD4 = none;
	m_previousGamepadRStickD4 = none;

	m_isActive = false;
}


void InputManager::beginFrame()
{
	if (not Window::GetState().focused)
	{
		m_state = InputState{};

		m_leftStopwatch.reset();
		m_rightStopwatch.reset();
		m_upStopwatch.reset();
		m_downStopwatch.reset();

		return;
	}

	m_inputs = m_keyboard;
	m_inputs.leftStick.x = m_keyboard.right.pressed() - m_keyboard.left.pressed();
	m_inputs.leftStick.y = m_keyboard.down.pressed() - m_keyboard.up.pressed();

	Print << m_inputs.left.pressed() << U", " << m_inputs.right.pressed() << U", " << m_inputs.up.pressed() << U", " << m_inputs.down.pressed();

	updateXInput();
	updateProCon();
	updateGamepad();

	updateLeft();
	updateRight();
	updateUp();
	updateDown();
	updateApply();
	updateCancel();
	updatePause();

	updateLeftStick();

	updateLeftLongPress();
	updateRightLongPress();
	updateUpLongPress();
	updateDownLongPress();
}


void InputManager::updateXInput()
{
	const size_t playerIndex = 0;

	if (m_xController = XInput(playerIndex))
	{
		InputSet xinput;

		xinput.left = { m_xController.buttonLeft };
		xinput.right = { m_xController.buttonRight };
		xinput.up = { m_xController.buttonUp };
		xinput.down = { m_xController.buttonDown };

		xinput.leftStick.x = m_xController.leftThumbX;
		xinput.leftStick.y = m_xController.leftThumbY;

		xinput.apply = { m_xController.buttonA };
		xinput.cancel = { m_xController.buttonB };
		xinput.pause = { m_xController.buttonMenu };

		m_inputs += xinput;

		m_previousXLStickD4 = m_xController.leftThumbD4();
		m_previousXRStickD4 = m_xController.rightThumbD4();
	}
	else
	{
		m_previousXLStickD4 = none;
		m_previousXRStickD4 = none;
	}
}

void InputManager::updateProCon()
{
	const size_t playerIndex = 0;

	if (m_proController = ProController{ playerIndex })
	{
		InputSet procon;

		procon.left = { m_proController.povLeft };
		procon.right = { m_proController.povRight };
		procon.up = { m_proController.povUp };
		procon.down = { m_proController.povDown };

		procon.leftStick = m_proController.LStick();

		procon.apply = { m_proController.buttonA };
		procon.cancel = { m_proController.buttonB };
		procon.pause = { m_proController.buttonPlus };

		m_inputs += procon;

		m_previousProLStickD4 = proLeftStickD4();
		m_previousProRStickD4 = proRightStickD4();
	}
	else
	{
		m_previousProLStickD4 = none;
		m_previousProRStickD4 = none;
	}
}

void InputManager::updateGamepad()
{
	const size_t playerIndex = 0;

	if (m_gamepad = Gamepad(playerIndex))
	{
		InputSet gamepad;

		gamepad.left = { m_gamepad.buttons[17] };
		gamepad.right = { m_gamepad.buttons[15] };
		gamepad.up = { m_gamepad.buttons[14] };
		gamepad.down = { m_gamepad.buttons[16] };

		gamepad.leftStick.x = m_gamepad.axes[0];
		gamepad.leftStick.y = m_gamepad.axes[1];

		// ×
		gamepad.apply = { m_gamepad.buttons[1] };
		// 〇
		gamepad.cancel = { m_gamepad.buttons[2] };
		// OPTIONS
		gamepad.pause = { m_gamepad.buttons[9] };

		m_inputs += gamepad;

		m_previousGamepadLStickD4 = gamepadLeftStickD4();
		m_previousGamepadRStickD4 = gamepadRightStickD4();
	}
	else
	{
		m_previousGamepadLStickD4 = none;
		m_previousGamepadRStickD4 = none;
	}
}


void InputManager::updateLeft()
{
	const InputGroup& left = m_inputs.left;
	const uint8 direction = 3;

	m_state.leftDown = left.down() || leftStickD4Down(direction);
	m_state.leftPressed = left.pressed() || leftStickD4Pressed(direction);
	m_state.leftUp = left.up() || leftStickD4Up(direction);
}

void InputManager::updateRight()
{
	const InputGroup& right = m_inputs.right;
	const uint8 direction = 1;

	m_state.rightDown = right.down() || leftStickD4Down(direction);
	m_state.rightPressed = right.pressed() || leftStickD4Pressed(direction);
	m_state.rightUp = right.up() || leftStickD4Up(direction);
}

void InputManager::updateUp()
{
	const InputGroup& up = m_inputs.up;
	const uint8 direction = 0;

	m_state.upDown = up.down() || leftStickD4Down(direction);
	m_state.upPressed = up.pressed() || leftStickD4Pressed(direction);
	m_state.upUp = up.up() || leftStickD4Up(direction);
}

void InputManager::updateDown()
{
	const InputGroup& down = m_inputs.down;
	const uint8 direction = 2;

	m_state.downDown = down.down() || leftStickD4Down(direction);
	m_state.downPressed = down.pressed() || leftStickD4Pressed(direction);
	m_state.downUp = down.up() || leftStickD4Up(direction);
}


void InputManager::updateLeftStick()
{
	m_state.leftStick = m_inputs.leftStick;

	if (1.0 < m_state.leftStick.length())
	{
		m_state.leftStick.setLength(1.0);
	}
}


void InputManager::updateApply()
{
	const InputGroup& apply = m_inputs.apply;

	m_state.applyDown = apply.down();
	m_state.applyPressed = apply.pressed();
	m_state.applyUp = apply.up();
}

void InputManager::updateCancel()
{
	const InputGroup& cancel = m_inputs.cancel;

	m_state.cancelDown = cancel.down();
	m_state.cancelPressed - cancel.pressed();
	m_state.cancelUp = cancel.up();
}

void InputManager::updatePause()
{
	const InputGroup& pause = m_inputs.pause;

	m_state.pauseDown = pause.down();
	m_state.pausePressed = pause.pressed();
	m_state.pauseUp = pause.up();
}


bool InputManager::leftStickD4Down(const uint8 direction) const
{
	const uint8 min = 0;
	const uint8 max = 3;

	if (not InRange(direction, min, max))
	{
		return false;
	}

	bool xinput = m_xController.leftThumbD4() == direction && m_previousXLStickD4 != direction;
	bool procon = proLeftStickD4() == direction && m_previousProLStickD4 != direction;
	bool gamepad = gamepadLeftStickD4() == direction && m_previousGamepadLStickD4 != direction;

	return xinput || procon || gamepad;
}

bool InputManager::leftStickD4Pressed(const uint8 direction) const
{
	const uint8 min = 0;
	const uint8 max = 3;

	if (not InRange(direction, min, max))
	{
		return false;
	}

	bool xinput = m_xController.leftThumbD4() == direction;
	bool procon = proLeftStickD4() == direction;
	bool gamepad = gamepadLeftStickD4() == direction;

	return xinput || procon || gamepad;
}

bool InputManager::leftStickD4Up(const uint8 direction) const
{
	const uint8 min = 0;
	const uint8 max = 3;

	if (not InRange(direction, min, max))
	{
		return false;
	}

	bool xinput = m_previousXLStickD4 == direction && m_xController.leftThumbD4() != direction;
	bool procon = m_previousProLStickD4 == direction && proLeftStickD4() != direction;
	bool gamepad = m_previousGamepadLStickD4 == direction && gamepadLeftStickD4() != direction;

	return xinput || procon || gamepad;
}


void InputManager::updateLeftLongPress()
{
	if (m_state.leftDown)
	{
		m_leftStopwatch.restart();
	}
	else if (m_state.leftUp)
	{
		m_leftStopwatch.reset();
	}

	bool longPressed = false;

	if (m_longPressThreshold < m_leftStopwatch.sF())
	{
		m_leftStopwatch.set(Duration{ m_leftStopwatch.sF() - m_longPressThreshold });
		longPressed = true;
	}

	m_state.leftLongPressed = m_state.leftPressed && longPressed;
}

void InputManager::updateRightLongPress()
{
	if (m_state.rightDown)
	{
		m_rightStopwatch.restart();
	}
	else if (m_state.rightUp)
	{
		m_rightStopwatch.reset();
	}

	bool longPressed = false;

	if (m_longPressThreshold < m_rightStopwatch.sF())
	{
		m_rightStopwatch.set(Duration{ m_rightStopwatch.sF() - m_longPressThreshold });
		longPressed = true;
	}

	m_state.rightLogPressed = m_state.rightPressed && longPressed;
}

void InputManager::updateUpLongPress()
{
	if (m_state.upDown)
	{
		m_upStopwatch.restart();
	}
	else if (m_state.upUp)
	{
		m_upStopwatch.reset();
	}

	bool longPressed = false;

	if (m_longPressThreshold < m_upStopwatch.sF())
	{
		m_upStopwatch.set(Duration{ m_upStopwatch.sF() - m_longPressThreshold });
		longPressed = true;
	}

	m_state.upLongPressed = m_state.upPressed && longPressed;
}

void InputManager::updateDownLongPress()
{
	if (m_state.downDown)
	{
		m_downStopwatch.restart();
	}
	else if (m_state.downUp)
	{
		m_downStopwatch.reset();
	}

	bool longPressed = false;

	if (m_longPressThreshold < m_downStopwatch.sF())
	{
		m_downStopwatch.set(Duration{ m_downStopwatch.sF() - m_longPressThreshold });
		longPressed = true;
	}

	m_state.downLongPressed = m_state.downPressed && longPressed;
}


Optional<uint8> InputManager::proLeftStickD4(double threshold) const
{
	threshold = Clamp(threshold, 0.0, 1.0);

	Vec2 stick = m_proController.LStick();

	double x = abs(stick.x);
	double y = abs(stick.y);

	if (x < threshold && y < threshold)
	{
		return none;
	}

	if (y <= x)
	{
		if (stick.x < 0)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (stick.y < 0)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
}

Optional<uint8> InputManager::proRightStickD4(double threshold) const
{
	threshold = Clamp(threshold, 0.0, 1.0);

	Vec2 stick = m_proController.RStick();

	double x = abs(stick.x);
	double y = abs(stick.y);

	if (x < threshold && y < threshold)
	{
		return none;
	}

	if (y <= x)
	{
		if (stick.x < 0)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (stick.y < 0)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
}


Optional<uint8> InputManager::gamepadLeftStickD4(double threshold) const
{
	if (not m_gamepad.isConnected())
	{
		return none;
	}
	if (m_xController.isConnected() || m_proController.isConnected())
	{
		return none;
	}

	threshold = Clamp(threshold, 0.0, 1.0);

	Vec2 stick = { m_gamepad.axes[0], m_gamepad.axes[1] };

	double x = abs(stick.x);
	double y = abs(stick.y);

	if (x < threshold && y < threshold)
	{
		return none;
	}

	if (y <= x)
	{
		if (stick.x < 0)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (stick.y < 0)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
}

Optional<uint8> InputManager::gamepadRightStickD4(double threshold) const
{
	if (not m_gamepad.isConnected())
	{
		return none;
	}
	if (m_xController.isConnected() || m_proController.isConnected())
	{
		return none;
	}

	threshold = Clamp(threshold, 0.0, 1.0);

	Vec2 stick = { m_gamepad.axes[2], m_gamepad.axes[5] };

	double x = abs(stick.x);
	double y = abs(stick.y);

	if (x < threshold && y < threshold)
	{
		return none;
	}

	if (y <= x)
	{
		if (stick.x < 0)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (stick.y < 0)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
}


InputState InputManager::inputState() const
{
	return m_state;
}


void InputManager::setLongPressThreshold(const uint32 ms)
{
	m_longPressThreshold = (double)ms / 1000.0;
}
