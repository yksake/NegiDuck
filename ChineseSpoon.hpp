﻿#pragma once
#include "GameObject.hpp"

class ChineseSpoon : public GameObject
{
public:
	ChineseSpoon(const Vec2& pos);

	void draw() const override;

	void pause() override;
	void resume() override;


private:
	static constexpr SizeF m_Size = { 100, 50 };
};
