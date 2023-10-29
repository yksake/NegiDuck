#include "Bomb.hpp"

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
		hitEvent(duck);
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
		hitEvent(duck);
	}
}

void Bomb::hitEvent(Duck& duck)
{
	const double rejectSpeed = 9;
	const double recoveryTimer = 0.5;
	Vec2 reject = { duck.pos().x - m_pos.x, duck.pos().y - m_pos.y };
	reject.setLength(rejectSpeed);

	duck.setSpeed(Vec2::Zero());
	duck.setEnvironmentalSpeed(reject);
	duck.consumeStamina(20);
	duck.startRecoveryTime(recoveryTimer);

	m_texture = Texture{ U"💥"_emoji };
	m_animationTimer.start();
	m_isActive = false;
}


void Bomb::pause()
{

}

void Bomb::resume()
{

}
