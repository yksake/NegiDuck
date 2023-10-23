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

	m_previousVelocity = m_velocity;
	m_velocity = Vec2::Zero();

	// Move
	{
		m_speed += input.leftStick * m_MoveVelocity * Scene::DeltaTime();

		if (input.leftStick.x == 0)
		{
			m_speed.x *= m_Registance * Scene::DeltaTime() / (1.0 / 60.0);
		}
		if (input.leftStick.y == 0)
		{
			m_speed.y *= m_Registance * Scene::DeltaTime() / (1.0 / 60.0);
		}

		if (m_TerminalVelocity < m_speed.length())
		{
			m_speed.setLength(m_TerminalVelocity);
		}

		m_velocity = m_speed;

		if (m_velocity.x < 0)
		{
			if (0 <= m_previousVelocity.x)
			{
				m_animationTimer.restart();
			}

			m_isRight = false;
		}
		else if (0 < m_velocity.x)
		{
			if (m_previousVelocity.x <= 0)
			{
				m_animationTimer.restart();
			}

			m_isRight = true;
		}
		else
		{
			if (m_animationTimer.isStarted())
			{
				m_animationTimer.reset();
			}
		}
	}
}

void Duck::draw() const
{
	viewRegion()(m_texture.mirrored(m_isRight)).draw();
}


void Duck::setSpeedX(const double& speedX)
{
	m_speed.x = speedX;
}

void Duck::setSpeedY(const double& speedY)
{
	m_speed.y = speedY;
}


bool Duck::isRight() const
{
	return m_isRight;
}

void Duck::setDirection(const bool isRight)
{
	m_isRight = isRight;
}


Vec2 Duck::velocity() const
{
	return m_velocity;
}


void Duck::pause()
{
	m_animationTimer.pause();
}

void Duck::resume()
{
	m_animationTimer.resume();
}
