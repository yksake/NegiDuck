#pragma once
#include "Ingredient.hpp"

class GreenOnion : public Ingredient
{
public:
	GreenOnion(const Vec2& pos);

	void update() override;
	void draw() const override;

	void hitEventLR(Duck& duck) override;
	void hitEventTB(Duck& duck) override;

	void pause() override;
	void resume() override;


private:

};
