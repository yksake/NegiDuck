#pragma once
#include "GameObject.hpp"

class ChineseSpoon : public GameObject
{
public:
	ChineseSpoon(const Vec2& pos, const uint8 maxCnt);

	void draw() const override;

	void takeInGreenOnion(const uint8 cnt);

	void pause() override;
	void resume() override;


private:
	uint8 m_maxCnt = 0;
	uint8 m_cnt = 0;
};
