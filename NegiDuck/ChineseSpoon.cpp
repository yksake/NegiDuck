#include "ChineseSpoon.hpp"

ChineseSpoon::ChineseSpoon(const Vec2& pos, const uint8 maxCnt)
	: GameObject(pos, SizeF{ 95, 35 }, SizeF{ 205, 145 })
{
	m_texture = Texture{ Resource(U"img/ChineseSpoon.png") };
	m_maxCnt = maxCnt;
}


void ChineseSpoon::draw() const
{
	const Size clipSize = { 41, 29 };
	uint8 textureCnt = 0;
	const double percentage = (double)m_cnt / (double)m_maxCnt;

	if (0.75 < percentage)
	{
		textureCnt = 4;
	}
	else if (0.50 < percentage)
	{
		textureCnt = 3;
	}
	else if (0.25 < percentage)
	{
		textureCnt = 2;
	}
	else if (0.0 < percentage)
	{
		textureCnt = 1;
	}

	const Rect clip = { clipSize.x * textureCnt, 0, clipSize };

	viewRegion()(m_texture(clip)).draw();
}


void ChineseSpoon::takeInGreenOnion(const uint8 cnt)
{
	m_cnt += cnt;

	if (m_maxCnt < m_cnt)
	{
		m_cnt = m_maxCnt;
	}
}


void ChineseSpoon::pause()
{

}

void ChineseSpoon::resume()
{

}
