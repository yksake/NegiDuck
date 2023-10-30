#include "ChineseSpoon.hpp"

ChineseSpoon::ChineseSpoon(const Vec2& pos) : GameObject(pos, SizeF{ 95, 35 }, SizeF{ 205, 145 })
{
	m_texture = Texture{ U"img/ChineseSpoon.png" };
}


void ChineseSpoon::draw() const
{
	viewRegion()(m_texture).draw();
}


void ChineseSpoon::pause()
{

}

void ChineseSpoon::resume()
{

}
