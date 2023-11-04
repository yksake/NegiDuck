#include "RamenTimer.hpp"
#include "Font/PixelCube.hpp"

RamenTimer::RamenTimer()
{
	
}

RamenTimer::RamenTimer(const Vec2& pos)
{
	m_pos = pos;
}


void RamenTimer::draw() const
{
	String time;
	const uint8 fontSize = 5;
	const Color color{ 50 };

	// minute
	if (60 <= m_stopwatch.min())
	{
		time = U"59";
	}
	else
	{
		time += U"{:0>2}"_fmt(m_stopwatch.min());
	}

	// colon
	time += U":";

	// seconds
	if (60 <= m_stopwatch.min())
	{
		time = U"59";
	}
	else
	{
		time += U"{:0>2}"_fmt(m_stopwatch.s() % 60);
	}

	PixelCube::Draw(time, fontSize, Arg::center = m_pos, color);
}


void RamenTimer::start()
{
	m_stopwatch.restart();
}

void RamenTimer::pause()
{
	m_stopwatch.pause();
}

void RamenTimer::resume()
{
	m_stopwatch.resume();
}


PlayTime RamenTimer::get() const
{
	PlayTime time;

	time.minutes = Minutes{ m_stopwatch.min() };
	time.seconds = Seconds{ m_stopwatch.s() % 60 };
	time.ms = Milliseconds{ m_stopwatch.ms() % 1000 };

	return time;
}
