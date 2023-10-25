#include "ChineseSpoon.hpp"

ChineseSpoon::ChineseSpoon(const Vec2& pos) : GameObject(pos, Vec2{ 100, 50 })
{
	m_texture = Texture{ U"img/renge_spoon.png" };
}


void ChineseSpoon::draw() const
{
	m_texture
		.scaled(0.35)
		.drawAt(hitRegion().tl() + Vec2{ 70, 0 });

	hitRegion().draw(Color{ 0, 255, 0, 100 });
}


void ChineseSpoon::pause()
{

}

void ChineseSpoon::resume()
{

}
