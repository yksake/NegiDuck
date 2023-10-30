#include "Bomb.hpp"

Bomb::Bomb(const Vec2& pos) : Ingredient(pos, SizeF{ 50, 50 }, SizeF{ 70, 70 })
{
	m_texture = Texture{ U"img/Bomb.png" };
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

	const Size clipSize = { 14, 14 };
	Rect clip = { 0, 0, clipSize };

	if (m_animationTimer.isStarted())
	{
		clip.moveBy(clipSize.x, 0);
	}

	viewRegion()(m_texture(clip)).draw();
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

	m_animationTimer.restart();
	m_isActive = false;
}


void Bomb::pause()
{

}

void Bomb::resume()
{

}
