#include "GreenOnion.hpp"

GreenOnion::GreenOnion(const Vec2& pos) : GameObject(pos, m_Size)
{

}


void GreenOnion::draw() const
{
	if (not isAlive())
	{
		return;
	}

	Circle{viewRegion().center(), m_Size.x / 2}.drawFrame(0, 8, Palette::Limegreen);
}


void GreenOnion::pause()
{

}

void GreenOnion::resume()
{

}
