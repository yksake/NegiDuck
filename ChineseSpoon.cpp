#include "ChineseSpoon.hpp"

ChineseSpoon::ChineseSpoon(const Vec2& pos) : GameObject(pos, Vec2{ 70, 50 })
{
	m_texture = Texture{ U"img/renge_spoon.png" };
}


void ChineseSpoon::draw() const
{
	m_texture
		.scaled(0.35)
		.drawAt(hitRegion().tl() + Vec2{ 50, 0 });
}


void ChineseSpoon::pause()
{

}

void ChineseSpoon::resume()
{

}
