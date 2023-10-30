#include "RamenBowl.hpp"
#include "Bomb.hpp"

RamenBowl::RamenBowl(const uint8 stageNum, const RectF& area)
{
	m_raimon = Texture{ U"img/Raimon.png" };

	m_gameArea = area;

	cook(stageNum);
}

void RamenBowl::cook(const uint8 stageNum)
{
	m_noodles.clear();
	m_greenOnions.clear();
	m_objects.clear();

	if (stageNum == 0)
	{
		m_spoon = ChineseSpoon{ m_gameArea.tr().movedBy(-85, 0) };

		m_noodles << Noodle{ m_gameArea.center() + Vec2{250, 0}, 6, true };
		m_noodles << Noodle{ Vec2{450, 460}, 9, false };

		m_greenOnions << GreenOnion{ m_gameArea.center() - Vec2{200, 100}};
		m_greenOnions << GreenOnion{ m_gameArea.center() + Vec2{-420, 180} };
		m_greenOnions << GreenOnion{ Vec2{760, 430} };
		m_greenOnions << GreenOnion{ Vec2{1005, 540} };

		m_objects << std::make_unique<Bomb>(m_gameArea.center() - Vec2{400, 180});
		m_objects << std::make_unique<Bomb>(Vec2{ 665, 620 });
		m_objects << std::make_unique<Bomb>(Vec2{ 1080, 370 });
	}
}


void RamenBowl::update()
{
	for (auto&& noodle : m_noodles)
	{
		noodle.update();
	}
	for (auto&& greenOnion : m_greenOnions)
	{
		greenOnion.update();
	}
	for (auto&& object : m_objects)
	{
		object->update();
	}
}

void RamenBowl::draw() const
{
	// Soup
	{
		const Color color{ 224, 184, 159 };
		m_gameArea.draw(color);
	}

	// Wall
	{
		const Color color{ 50 };

		RectF left = { 0, m_gameArea.topY(), m_gameArea.leftX(), m_gameArea.h };
		left = left.stretched(55, 0, 0, 0);
		left.draw(color);

		RectF right = left.movedBy(m_gameArea.rightX() - left.leftX(), 0);
		right.draw(color);
	}

	m_spoon.draw();

	for (const auto& noodle : m_noodles)
	{
		noodle.draw();
	}
	for (const auto& object : m_objects)
	{
		object->draw();
	}
	for (const auto& greenOnion : m_greenOnions)
	{
		greenOnion.draw();
	}

	m_raimon.scaled(5).draw();
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
	const double StaminaRecoverSpeed = 30.0;
	const Vec2 duckSpeed = duck.speed();

	// Move X
	{
		duck.moveX(duck.velocity().x);

		if (duck.leftX() < m_gameArea.leftX())
		{
			duck.moveX(m_gameArea.leftX() - duck.leftX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}
		else if (m_gameArea.rightX() < duck.rightX())
		{
			duck.moveX(m_gameArea.rightX() - duck.rightX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}
	}

	// Move Y
	{
		duck.moveY(m_gameArea.topY() - duck.bottomY());

		if (input.downPressed)
		{
			duck.diveDown();
			duck.moveY(m_gameArea.topY() - duck.topY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeed(Vec2::Zero());
			return;
		}
	}

	duck.recoverStamina(StaminaRecoverSpeed * Scene::DeltaTime());

	// Chinese Spoon
	if (m_spoon.isHit(duck))
	{
		duck.putGreenOnion();

		m_greenOnions.remove_if([](const GreenOnion& go) { return not go.isAlive(); });
	}
}

void RamenBowl::checkSwimming(Duck& duck, const dss::InputState& input)
{
	const double staminaDecreaseSpeed = 6.0;
	const Vec2 duckSpeed = duck.speed();

	// Move X
	{
		duck.moveX(duck.velocity().x);

		if (duck.leftX() < m_gameArea.leftX())
		{
			duck.moveX(m_gameArea.leftX() - duck.leftX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}
		else if (m_gameArea.rightX() < duck.rightX())
		{
			duck.moveX(m_gameArea.rightX() - duck.rightX());
			duck.setSpeedX(0);
			duck.setEnvironmentalSpeedX(0);
		}

		for (auto&& noodle : m_noodles)
		{
			noodle.hitEventLR(duck);
		}
		for (auto&& object : m_objects)
		{
			object->hitEventLR(duck);
		}
		for (auto&& greenOnion : m_greenOnions)
		{
			greenOnion.hitEventLR(duck);
		}
	}

	// Move Y
	{
		duck.moveY(duck.velocity().y);

		if (duck.topY() < m_gameArea.topY())
		{
			duck.moveY(m_gameArea.topY() - duck.topY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeedY(0);

			if (input.upPressed)
			{
				duck.floatUp();
				duck.moveY(m_gameArea.topY() - duck.bottomY());
				return;
			}
		}
		else if (m_gameArea.bottomY() < duck.bottomY())
		{
			duck.moveY(m_gameArea.bottomY() - duck.bottomY());
			duck.setSpeedY(0);
			duck.setEnvironmentalSpeedY(0);
		}

		for (auto&& noodle : m_noodles)
		{
			noodle.hitEventTB(duck);
		}
		for (auto&& object : m_objects)
		{
			object->hitEventTB(duck);
		}
		for (auto&& greenOnion : m_greenOnions)
		{
			greenOnion.hitEventTB(duck);
		}
	}

	duck.consumeStamina(staminaDecreaseSpeed * Scene::DeltaTime());
}


bool RamenBowl::isCompleted() const
{
	return m_greenOnions.isEmpty();
}


void RamenBowl::pause()
{
	m_spoon.pause();

	for (auto&& greenOnion : m_greenOnions)
	{
		greenOnion.pause();
	}

	for (auto&& object : m_objects)
	{
		object->pause();
	}
}

void RamenBowl::resume()
{
	m_spoon.resume();

	for (auto&& greenOnion : m_greenOnions)
	{
		greenOnion.resume();
	}

	for (auto&& object : m_objects)
	{
		object->resume();
	}
}
