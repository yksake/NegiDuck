#include "Bomb.hpp"

const double Bomb::m_RejectSpeed = 9;


Bomb::Bomb(const Vec2& pos) : Ingredient(pos, Vec2{ 50, 50 })
{
	m_texture = Texture{ U"💣"_emoji };
}


void Bomb::update()
{
	if (m_animationTimer.reachedZero())
	{
		kill();
	}
}

void Bomb::draw() const
{
	if (not isAlive())
	{
		return;
	}

	viewRegion()(m_texture).draw();
}


void Bomb::hitEventLR(Duck& duck)
{
	if (not m_isActive)
	{
		return;
	}

	if (isHit(duck))
	{
		Vec2 reject = { duck.pos().x - m_pos.x, duck.pos().y - m_pos.y };
		reject.setLength(m_RejectSpeed);

		duck.setSpeed(Vec2::Zero());
		duck.setEnvironmentalSpeed(reject);

		m_texture = Texture{ U"💥"_emoji };
		m_animationTimer.start();
		m_isActive = false;
	}
}

void Bomb::hitEventTB(Duck& duck)
{
	if (not m_isActive)
	{
		return;
	}

	if (isHit(duck))
	{
		Vec2 reject = { duck.pos().x - m_pos.x, duck.pos().y - m_pos.y };
		reject.setLength(m_RejectSpeed);

		duck.setSpeed(Vec2::Zero());
		duck.setEnvironmentalSpeed(reject);

		m_texture = Texture{ U"💥"_emoji };
		m_animationTimer.start();
		m_isActive = false;
	}
}


void Bomb::pause()
{

}

void Bomb::resume()
{

}
