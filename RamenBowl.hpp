#pragma once
#include "ChineseSpoon.hpp"
#include "Noodle.hpp"
#include "GreenOnion.hpp"
#include "Ingredient.hpp"

class RamenBowl
{
public:
	RamenBowl();

	void update();
	void draw() const;

	void check(Duck& duck, const dss::InputState& input);

	bool isCompleted() const;


private:
	ChineseSpoon m_spoon{ Vec2{ 1030, 75 } };
	Array<Noodle> m_noodles;
	Array<GreenOnion> m_greenOnions;
	Array<std::unique_ptr<Ingredient>> m_objects;

	static constexpr RectF m_GameArea = { 100, 100, 1080, 520 };


	void checkFloating(Duck& duck, const dss::InputState& input);
	void checkSwimming(Duck& duck, const dss::InputState& input);
};
