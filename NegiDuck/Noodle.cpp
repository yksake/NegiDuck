#include "Noodle.hpp"

const double Noodle::m_BoundSpeed = 7;
const double Noodle::m_RecoveryTime = 0.2;


Noodle::Noodle(const Vec2& pos, const SizeF& size) : Ingredient(pos, size)
{

}


void Noodle::update()
{

}

void Noodle::draw() const
{
	viewRegion().draw(Palette::Lemonchiffon);
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
