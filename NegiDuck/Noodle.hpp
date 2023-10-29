#pragma once
#include "Ingredient.hpp"

class Noodle : public Ingredient
{
public:
	Noodle(const Vec2& pos, const SizeF& size);

	void update() override;
	void draw() const override;

	void hitEventLR(Duck& duck) override;
	void hitEventTB(Duck& duck) override;

	void pause() override;
	void resume() override;


private:
	static const double m_BoundSpeed;
};
