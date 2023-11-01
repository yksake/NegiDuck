#pragma once
#include <Siv3D.hpp>

class PlayTime
{
public:
	Minutes minutes;
	Seconds seconds;
	Milliseconds ms;


	PlayTime();

	bool isZero() const;

	bool operator ==(const PlayTime& pt) const
	{
		if (this->minutes != pt.minutes)
		{
			return false;
		}
		if (this->seconds != pt.seconds)
		{
			return false;
		}
		if (this->ms != pt.ms)
		{
			return false;
		}

		return true;
	}

	bool operator <(const PlayTime& pt) const
	{
		if (this->minutes < pt.minutes)
		{
			return true;
		}
		else if (pt.minutes < this->minutes)
		{
			return false;
		}

		if (this->seconds < pt.seconds)
		{
			return true;
		}
		else if (pt.seconds < this->seconds)
		{
			return false;
		}

		if (this->ms < pt.ms)
		{
			return true;
		}
		else if (pt.ms < this->ms)
		{
			return false;
		}

		return false;
	}
};
