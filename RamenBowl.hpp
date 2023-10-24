#pragma once
#include "Noodle.hpp"
#include "Ingredient.hpp"

class RamenBowl
{
public:
	RamenBowl();

	void update();
	void draw() const;

	void check(Duck& duck, const dss::InputState& input);


private:
	Array<Noodle> m_noodles;
	Array<std::unique_ptr<Ingredient>> m_items;

	static constexpr RectF m_GameArea = { 100, 100, 1080, 520 };


	void checkFloating(Duck& duck, const dss::InputState& input);
	void checkSwimming(Duck& duck, const dss::InputState& input);
};
