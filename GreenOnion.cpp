﻿#include "GreenOnion.hpp"

GreenOnion::GreenOnion(const Vec2& pos) : Ingredient(pos, Vec2{ 50, 50 })
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

	Circle{m_pos, m_viewSize.x / 2}.drawFrame(8, 0, Palette::Limegreen);
}


void GreenOnion::hitEventLR(Duck& duck)
{
	if (not isAlive())
	{
		return;
	}

	if (isHit(duck))
	{
		duck.getGreenOnion();

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
		duck.getGreenOnion();

		kill();
	}
}


void GreenOnion::pause()
{

}

void GreenOnion::resume()
{

}
