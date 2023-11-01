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
	const uint8 fontSize = 5;
	const Color color{ 50 };

	// minute
	{
		String text = U"{:0>2}"_fmt(m_stopwatch.min());
		const Vec2 pos = m_pos.movedBy(-2 * fontSize, 0);

		if (59 <= m_stopwatch.min())
		{
			text = U"59";
		}

		PixelCube::Draw(text, fontSize, Arg::rightCenter = pos, color);
	}

	// colon
	{
		PixelCube::Draw(U":", fontSize, Arg::center = m_pos, color);
	}

	// seconds
	{
		String text = U"{:0>2}"_fmt(m_stopwatch.s() % 60);
		const Vec2 pos = m_pos.movedBy(2 * fontSize, 0);

		if (100 <= m_stopwatch.min())
		{
			text = U"59";
		}

		PixelCube::Draw(text, fontSize, Arg::leftCenter = pos, color);
	}
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
