#include "Noodle.hpp"

Noodle::Noodle(const Vec2& pos, const SizeF& size) : GameObject(pos, size)
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
			duck.setSpeedX(-m_BoundSpeed);
		}
		// 右から接触
		else
		{
			duck.moveX(rightX() - duck.leftX());
			duck.setSpeedX(m_BoundSpeed);
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
			duck.setSpeedY(m_BoundSpeed);
		}
		// 上から接触
		else
		{
			duck.moveY(topY() - duck.bottomY());
			duck.setSpeedY(-m_BoundSpeed);
		}
	}
}


void Noodle::pause()
{

}

void Noodle::resume()
{

}
