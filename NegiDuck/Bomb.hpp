#pragma once
#include "Ingredient.hpp"

class Bomb : public Ingredient
{
public:
	Bomb(const Vec2& pos);

	void update() override;
	void draw() const override;

	void hitEventLR(Duck& duck) override;
	void hitEventTB(Duck& duck) override;

	void pause() override;
	void resume() override;


private:
	static const double m_RejectSpeed;
	bool m_isActive = true;
	Timer m_animationTimer{ Duration{ 1.0 } };


	void hitEvent(Duck& duck);
};
