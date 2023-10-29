#pragma once
#include "Duck.hpp"

class Ingredient : public GameObject
{
public:
	Ingredient(const Vec2& pos, const SizeF& hitSize, const SizeF& viewSize);
	Ingredient(const Vec2& pos, const SizeF& size);
	virtual ~Ingredient() = default;

	virtual void update() = 0;
	virtual void draw() const override = 0;

	virtual void hitEventLR(Duck& duck) = 0;
	virtual void hitEventTB(Duck& duck) = 0;

	virtual void pause() override = 0;
	virtual void resume() override = 0;
};
