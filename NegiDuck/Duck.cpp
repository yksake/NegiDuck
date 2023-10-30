#include "Duck.hpp"

const double Duck::m_Registance = 0.95;
const double Duck::m_MaxStamina = 100;


Duck::Duck(const Vec2& pos) : GameObject(pos, Vec2{ 40, 50 }, Vec2{ 80, 80 })
{
	//m_texture = Texture{ U"🦆"_emoji };
	m_texture = Texture{ U"img/Duck.png" };
}


void Duck::update(const dss::InputState& input)
{
	if (not isAlive())
	{
		return;
	}

	if (m_recoveryTimer.reachedZero())
	{
		m_recoveryTimer.reset();
	}
	if (m_dashTimer.reachedZero())
	{
		m_dashTimer.reset();
	}

	if (not input.leftStick.isZero())
	{
		m_lastLeftStick = input.leftStick;
	}

	const Vec2 previousVelocity = m_velocity;
	m_velocity = Vec2::Zero();

	updateMove(input.leftStick);

	if (input.applyDown)
	{
		dash();
	}

	m_environmentalSpeed *= m_Registance * Scene::DeltaTime() / (1.0 / 60.0);

	m_velocity = m_speed + m_environmentalSpeed;

	/*
	if (m_velocity.x < 0)
	{
		if (0 <= previousVelocity.x)
		{
			m_animationTimer.restart();
		}
	}
	else if (0 < m_velocity.x)
	{
		if (previousVelocity.x <= 0)
		{
			m_animationTimer.restart();
		}
	}
	else
	{
		if (m_animationTimer.isStarted())
		{
			m_animationTimer.reset();
		}
	}
	*/
}

void Duck::updateMove(Vec2 leftStick)
{
	const double moveSpeed = 7.0;
	const double terminalSpeed = 3.0;

	if (m_recoveryTimer.isRunning())
	{
		leftStick = Vec2::Zero();
	}
	
	m_speed += leftStick * moveSpeed * Scene::DeltaTime();

	if (leftStick.x == 0)
	{
		m_speed.x *= m_Registance * Scene::DeltaTime() / (1.0 / 60.0);
	}
	if (leftStick.y == 0)
	{
		m_speed.y *= m_Registance * Scene::DeltaTime() / (1.0 / 60.0);
	}

	if (terminalSpeed < m_speed.length())
	{
		m_speed.setLength(terminalSpeed);
	}

	if (leftStick.x < 0)
	{
		m_isRight = false;
	}
	else if (0 < leftStick.x)
	{
		m_isRight = true;
	}
}

void Duck::dash()
{
	if (m_isFloating)
	{
		return;
	}
	if (m_recoveryTimer.isRunning())
	{
		return;
	}
	if (m_dashTimer.isRunning())
	{
		return;
	}

	const double dashSpeed = 10;
	const double staminaDecrease = 10;

	if (m_stamina < staminaDecrease)
	{
		return;
	}

	if (m_lastLeftStick.isZero())
	{
		if (m_isRight)
		{
			m_lastLeftStick = { 1, 0 };
		}
		else
		{
			m_lastLeftStick = { -1, 0 };
		}
	}

	m_environmentalSpeed += m_lastLeftStick * dashSpeed;

	m_stamina -= staminaDecrease;

	m_dashTimer.restart();
}


void Duck::draw() const
{
	const Size clipSize = { 16, 16 };
	Rect clip = { 0, 0, clipSize };

	if (not m_isFloating)
	{
		clip.moveBy(clipSize.x, 0);
	}

	viewRegion()(m_texture(clip).mirrored(m_isRight)).draw();
}


Vec2 Duck::speed() const
{
	return m_speed;
}

void Duck::setSpeed(const Vec2& speed)
{
	m_speed = speed;
}

void Duck::setSpeedX(const double& speedX)
{
	m_speed.x = speedX;
}

void Duck::setSpeedY(const double& speedY)
{
	m_speed.y = speedY;
}


void Duck::setEnvironmentalSpeed(const Vec2& environmentalSpeed)
{
	m_environmentalSpeed = environmentalSpeed;
}

void Duck::setEnvironmentalSpeedX(const double& environmentalSpeedX)
{
	m_environmentalSpeed.x = environmentalSpeedX;
}

void Duck::setEnvironmentalSpeedY(const double& environmentalSpeedY)
{
	m_environmentalSpeed.y = environmentalSpeedY;
}


Vec2 Duck::velocity() const
{
	return m_velocity;
}


bool Duck::isFloating() const
{
	return m_isFloating;
}

void Duck::diveDown()
{
	m_isFloating = false;
}

void Duck::floatUp()
{
	m_isFloating = true;
}


bool Duck::isRight() const
{
	return m_isRight;
}

void Duck::setDirection(const bool isRight)
{
	m_isRight = isRight;
}


double Duck::staminaPercentage() const
{
	double percentage = m_stamina / m_MaxStamina;

	return percentage;
}

void Duck::recoverStamina(const double& recover)
{
	m_stamina += recover;

	if (m_MaxStamina < m_stamina)
	{
		m_stamina = m_MaxStamina;
	}
}

void Duck::consumeStamina(const double& consume)
{
	m_stamina -= consume;

	if (m_stamina < 0)
	{
		kill();
	}
}


void Duck::getGreenOnion()
{
	if (not isAlive())
	{
		return;
	}

	m_greenOnionCnt++;
}

uint8 Duck::putGreenOnion()
{
	if (not isAlive())
	{
		return 0;
	}

	const uint8 cnt = m_greenOnionCnt;

	m_greenOnionCnt = 0;

	return cnt;
}


void Duck::startRecoveryTime(const double& ms)
{
	m_recoveryTimer.restart(Duration{ ms });
}


void Duck::pause()
{
	m_animationTimer.pause();
}

void Duck::resume()
{
	m_animationTimer.resume();
}
