#include "PlayTime.hpp"

PlayTime::PlayTime()
{
	minutes = Minutes{ 0 };
	seconds = Seconds{ 0 };
	ms = Milliseconds{ 0 };
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
