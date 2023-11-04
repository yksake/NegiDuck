#pragma once
#include <Siv3D.hpp>

class PlayTime
{
public:
	Minutes minutes;
	Seconds seconds;
	Milliseconds ms;


	PlayTime();
	PlayTime(const uint32 min, const uint32 sec, const uint32 ms);

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

	PlayTime operator +(const PlayTime& pt) const
	{
		PlayTime time;

		time.ms = this->ms + pt.ms;
		time.seconds = Seconds{ time.ms.count() / 1000 };
		time.ms %= 1000;

		time.seconds += this->seconds + pt.seconds;
		time.minutes = Minutes{ time.seconds.count() / 60 };
		time.seconds %= 60;

		time.minutes += this->minutes + pt.minutes;

		return time;
	}

	PlayTime& operator +=(const PlayTime& pt)
	{
		this->ms += pt.ms;
		this->seconds += Seconds{ this->ms.count() / 1000 };
		this->ms %= 1000;

		this->seconds += pt.seconds;
		this->minutes += Minutes{ this->seconds.count() / 60 };
		this->seconds %= 60;

		this->minutes += pt.minutes;

		return *this;
	}
};
