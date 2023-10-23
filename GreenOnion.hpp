#pragma once
#include "GameObject.hpp"

class GreenOnion : public GameObject
{
public:
	GreenOnion(const Vec2& pos);

	void draw() const override;

	void pause() override;
	void resume() override;


private:
	static constexpr SizeF m_Size = { 30, 30 };
};
