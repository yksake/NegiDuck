#pragma once
#include "GameObject.hpp"
#include "Duck.hpp"

class Noodle : public GameObject
{
public:
	Noodle(const Vec2& pos, const SizeF& size);

	void draw() const override;

	void hitEventLR(Duck& duck);
	void hitEventTB(Duck& duck);

	void pause() override;
	void resume() override;


private:

};
