#pragma once
#include "ChineseSpoon.hpp"
#include "Noodle.hpp"
#include "GreenOnion.hpp"
#include "Ingredient.hpp"

class RamenBowl
{
public:
	RamenBowl(const uint8 stageNum, const RectF& area);

	void update();
	void draw() const;

	void check(Duck& duck, const dss::InputState& input);

	bool isCompleted() const;

	void pause();
	void resume();


private:
	RectF m_gameArea;

	ChineseSpoon m_spoon{ Vec2{ 1030, 75 } };
	Array<Noodle> m_noodles;
	Array<GreenOnion> m_greenOnions;
	Array<std::unique_ptr<Ingredient>> m_objects;


	void cook(const uint8 stageNum);

	void checkFloating(Duck& duck, const dss::InputState& input);
	void checkSwimming(Duck& duck, const dss::InputState& input);
};
