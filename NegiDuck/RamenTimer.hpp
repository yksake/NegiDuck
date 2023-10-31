#pragma once
#include <Siv3D.hpp>

class RamenTimer
{
public:
	RamenTimer();
	RamenTimer(const Vec2& pos);

	void draw() const;

	void start();
	void pause();
	void resume();


private:
	Vec2 m_pos = Vec2::Zero();
	Stopwatch m_stopwatch;
};
