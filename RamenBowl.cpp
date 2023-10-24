#include "RamenBowl.hpp"
#include "GreenOnion.hpp"
#include "Bomb.hpp"

RamenBowl::RamenBowl()
{
	m_noodles << Noodle{ Scene::CenterF() + Vec2{100, 50}, SizeF{20, 100} };

	m_items << std::make_unique<GreenOnion>(Scene::CenterF() - Vec2{ 200, 0 });
	m_items << std::make_unique<Bomb>(Scene::CenterF() - Vec2{ 0, 200 });
}


void RamenBowl::update()
{
	for (auto&& noodle : m_noodles)
	{
		noodle.update();
	}
	for (auto&& item : m_items)
	{
		item->update();
	}
}

void RamenBowl::draw() const
{
	m_GameArea.drawFrame(0, 5, Palette::White);

	for (const auto& noodle : m_noodles)
	{
		noodle.draw();
	}
	for (const auto& item : m_items)
	{
		item->draw();
	}
}


void RamenBowl::check(Duck& duck, const dss::InputState& input)
{
	if (duck.isFloating())
	{
		checkFloating(duck, input);
	}
	else
	{
		checkSwimming(duck, input);
	}
}

void RamenBowl::checkFloating(Duck& duck, const dss::InputState& input)
{
	const Vec2 duckSpeed = duck.speed();

	// Move X
	{
		duck.moveX(duck.velocity().x);

		if (duck.leftX() < m_GameArea.leftX())
		{
			duck.moveX(m_GameArea.leftX() - duck.leftX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}
		else if (m_GameArea.rightX() < duck.rightX())
		{
			duck.moveX(m_GameArea.rightX() - duck.rightX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}
	}

	// Move Y
	{
		if (input.downPressed)
		{
			duck.diveDown();
			duck.moveY(duck.hitRegion().h);
			return;
		}
	}
}

void RamenBowl::checkSwimming(Duck& duck, const dss::InputState& input)
{
	const Vec2 duckSpeed = duck.speed();

	// Move X
	{
		duck.moveX(duck.velocity().x);

		if (duck.leftX() < m_GameArea.leftX())
		{
			duck.moveX(m_GameArea.leftX() - duck.leftX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}
		else if (m_GameArea.rightX() < duck.rightX())
		{
			duck.moveX(m_GameArea.rightX() - duck.rightX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}

		for (auto&& noodle : m_noodles)
		{
			noodle.hitEventLR(duck);
		}
		for (auto&& item : m_items)
		{
			item->hitEventLR(duck);
		}
	}

	// Move Y
	{
		duck.moveY(duck.velocity().y);

		if (duck.topY() < m_GameArea.topY())
		{
			duck.moveY(m_GameArea.topY() - duck.topY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeedY(0);

			if (input.upPressed)
			{
				duck.floatUp();
				duck.moveY(-duck.hitRegion().h);
				return;
			}
		}
		else if (m_GameArea.bottomY() < duck.bottomY())
		{
			duck.moveY(m_GameArea.bottomY() - duck.bottomY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeedY(0);
		}

		for (auto&& noodle : m_noodles)
		{
			noodle.hitEventTB(duck);
		}
		for (auto&& item : m_items)
		{
			item->hitEventTB(duck);
		}
	}
}
