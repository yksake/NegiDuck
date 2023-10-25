#include "Duck.hpp"

Duck::Duck(const Vec2& pos) : GameObject(pos, m_HitSize, m_ViewSize)
{
	m_texture = Texture{ U"🦆"_emoji };
}


void Duck::update(const dss::InputState& input)
{
	if (not isAlive())
	{
		return;
	}

	const Vec2 previousVelocity = m_velocity;
	m_velocity = Vec2::Zero();

	updateMove(input.leftStick);

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
}

void Duck::updateMove(const Vec2& leftStick)
{
	const double moveSpeed = 7.0;
	const double terminalSpeed = 3.0;
	const double registance = 0.95;
	
	m_speed += leftStick * moveSpeed * Scene::DeltaTime();

	if (leftStick.x == 0)
	{
		m_speed.x *= registance * Scene::DeltaTime() / (1.0 / 60.0);
	}
	if (leftStick.y == 0)
	{
		m_speed.y *= registance * Scene::DeltaTime() / (1.0 / 60.0);
	}

	if (terminalSpeed < m_speed.length())
	{
		m_speed.setLength(terminalSpeed);
	}

	m_environmentalSpeed *= registance * Scene::DeltaTime() / (1.0 / 60.0);

	m_velocity = m_speed + m_environmentalSpeed;

	// Set Direction
	if (leftStick.x < 0)
	{
		m_isRight = false;
	}
	else if (0 < leftStick.x)
	{
		m_isRight = true;
	}
}

void Duck::draw() const
{
	if (m_isFloating)
	{
		hitRegion().draw(Color{ 255, 0, 0, 100 });
	}
	else
	{
		hitRegion().draw(Color{ 0, 0, 255, 100 });
	}

	viewRegion()(m_texture.mirrored(m_isRight)).draw();
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


void Duck::pause()
{
	m_animationTimer.pause();
}

void Duck::resume()
{
	m_animationTimer.resume();
}
