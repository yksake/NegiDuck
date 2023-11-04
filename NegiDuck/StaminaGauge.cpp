#include "StaminaGauge.hpp"

StaminaGauge::StaminaGauge()
{
	m_icon = Texture{ Resource(U"img/Bubble.png") };
}

StaminaGauge::StaminaGauge(const Vec2& pos)
{
	m_icon = Texture{ Resource(U"img/Bubble.png") };
	m_pos = pos;
}


void StaminaGauge::draw(const double& percentage) const
{
	const Vec2 iconPos = m_pos;
	const Vec2 rectPos = m_pos + Vec2{ 0, 50 };
	const double width = 40;
	const double height = 485;
	const Color baseColor{ 172, 50, 50 };
	const Color airColor{ 95, 205, 228 };

	m_icon.scaled(5).draw(iconPos);

	RectF{ rectPos, width, height }.draw(baseColor);

	RectF{ rectPos, width, height * percentage }.draw(airColor);
}
