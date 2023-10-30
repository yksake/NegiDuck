#include "GreenOnion.hpp"

GreenOnion::GreenOnion(const Vec2& pos) : Ingredient(pos, SizeF{ 45, 50 }, SizeF{ 55, 60 })
{
	m_texture = Texture{ U"img/GreenOnion.png" };

	m_textureType = Random(0, 1);
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

	const Size clipSize = { 11, 12 };
	Rect clip = { 0, 0, clipSize };
	clip.x = clipSize.x * m_textureType;

	viewRegion()(m_texture(clip)).draw();
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
