#include "GreenOnion.hpp"

GreenOnion::GreenOnion(const Vec2& pos) : Ingredient(pos, m_Size)
{

}


void GreenOnion::update()
{

}

void GreenOnion::draw() const
{
	if (not isAlive())
	{
		return;
	}

	Circle{m_pos, m_Size.x / 2}.drawFrame(8, 0, Palette::Limegreen);
}


void GreenOnion::hitEventLR(Duck& duck)
{
	if (not isAlive())
	{
		return;
	}

	if (isHit(duck))
	{
		kill();
	}
}

void GreenOnion::hitEventTB(Duck& duck)
{
	if (not isAlive())
	{
		return;
	}

	if (isHit(duck))
	{
		kill();
	}
}


void GreenOnion::pause()
{

}

void GreenOnion::resume()
{

}
