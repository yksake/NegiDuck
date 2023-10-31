#pragma once

class StaminaGauge
{
public:
	StaminaGauge();
	StaminaGauge(const Vec2& pos);

	void draw(const double& percentage) const;


private:
	Texture m_icon;
	Vec2 m_pos = Vec2::Zero();
};
