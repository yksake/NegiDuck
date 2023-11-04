#include "PlayTime.hpp"

PlayTime::PlayTime()
{
	minutes = Minutes{ 0 };
	seconds = Seconds{ 0 };
	ms = Milliseconds{ 0 };
}

PlayTime::PlayTime(const uint32 min, const uint32 sec, const uint32 ms)
{
	this->ms = Milliseconds{ ms };
	seconds = Seconds{ this->ms.count() / 1000 };
	this->ms %= 1000;

	seconds += Seconds{ sec };
	minutes = Minutes{ seconds.count() / 60 };
	seconds %= 60;

	minutes += Minutes{ min };
}


bool PlayTime::isZero() const
{
	if (minutes != Minutes::zero())
	{
		return false;
	}
	if (seconds != Seconds::zero())
	{
		return false;
	}
	if (ms != Milliseconds::zero())
	{
		return false;
	}

	return true;
}
