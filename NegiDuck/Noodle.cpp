#include "Noodle.hpp"

const double Noodle::m_BoundSpeed = 7;
const double Noodle::m_RecoveryTime = 0.23;


Noodle::Noodle(const Vec2& pos, const uint8 length, const bool isVertical) : Ingredient(pos, SizeF::Zero())
{
	m_texture = Texture{ Resource(U"img/Noodle.png") };

	const double thickness = 20;
	const double baseLength = 40;

	if (isVertical)
	{
		m_hitSize = { thickness , baseLength * length };
	}
	else
	{
		m_hitSize = { baseLength * length, thickness };
	}

	m_viewSize = m_hitSize;
}


void Noodle::update()
{

}

void Noodle::draw() const
{
	const ScopedRenderStates2D sampler{ SamplerState::RepeatNearest };

	if (m_viewSize.x < m_viewSize.y)
	{
		const SizeF mapSize = SizeF{ m_viewSize.y, m_viewSize.x } / 5;

		m_texture.mapped(mapSize).scaled(5).rotated(90_deg).drawAt(m_pos);
	}
	else
	{
		const SizeF mapSize = m_viewSize / 5;

		m_texture.mapped(mapSize).scaled(5).drawAt(m_pos);
	}
}


void Noodle::hitEventLR(Duck& duck)
{
	if (isHit(duck))
	{
		// 左から接触
		if (0 < duck.velocity().x)
		{
			duck.moveX(leftX() - duck.rightX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(-m_BoundSpeed);
			duck.startRecoveryTime(m_RecoveryTime);
		}
		// 右から接触
		else
		{
			duck.moveX(rightX() - duck.leftX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(m_BoundSpeed);
			duck.startRecoveryTime(m_RecoveryTime);
		}
	}
}

void Noodle::hitEventTB(Duck& duck)
{
	if (isHit(duck))
	{
		// 下から接触
		if (duck.velocity().y < 0)
		{
			duck.moveY(bottomY() - duck.topY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeedY(m_BoundSpeed);
			duck.startRecoveryTime(m_RecoveryTime);
		}
		// 上から接触
		else
		{
			duck.moveY(topY() - duck.bottomY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeedY(-m_BoundSpeed);
			duck.startRecoveryTime(m_RecoveryTime);
		}
	}
}


void Noodle::pause()
{

}

void Noodle::resume()
{

}
