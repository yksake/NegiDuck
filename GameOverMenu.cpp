#include "GameOverMenu.hpp"
#include "Font/PixelChicken.hpp"

const Array<String> GameOverMenu::m_Menus = {
	U"RETRY",
	U"MAIN MENU"
};


GameOverMenu::GameOverMenu(const RectF& area) : AbstractMenu(area)
{
	m_stopwatch.reset();
}


bool GameOverMenu::update(const dss::InputState input)
{
	if (not isActive())
	{
		return false;
	}
	if (isClosing())
	{
		return false;
	}

	bool updated = false;

	if (input.upDown && 0 < m_index)
	{
		m_index--;
		updated = true;
	}
	if (input.downDown && m_index < m_MaxIndex)
	{
		m_index++;
		updated = true;
	}

	if (input.applyDown)
	{
		if (apply())
		{
			updated = true;
		}
	}

	return updated;
}

void GameOverMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	drawTitle();
	drawIndex();
}

void GameOverMenu::drawTitle() const
{
	if (not isActive())
	{
		return;
	}

	const String title = U"GAME OVER";
	const uint8 fontSize = 3;
	const Vec2 pos = m_area.center();
	const Color color = Palette::White;

	PixelChicken::Draw(title, fontSize, Arg::bottomCenter = pos, color);
}

void GameOverMenu::drawIndex() const
{
	if (not isActive())
	{
		return;
	}

	const uint8 fontSize = 2;
	const Color defaultColor{ 128 };
	const Color selectedColor = Palette::White;

	const double interval = 80;

	Vec2 pos = m_area.center();
	pos.y += interval * 0.75;

	for (uint8 i = 0; i < m_Menus.size(); i++)
	{
		Color color = defaultColor;

		if (i == m_index)
		{
			color = selectedColor;
		}

		PixelChicken::Draw(m_Menus[i], fontSize, Arg::topCenter = pos, color);

		pos.y += interval;
	}
}


bool GameOverMenu::isActive() const
{
	if (m_stopwatch.isRunning() && m_WaitTime <= m_stopwatch.ms())
	{
		m_stopwatch.pause();
	}

	return m_active && m_WaitTime <= m_stopwatch.ms();
}

MenuState GameOverMenu::state() const
{
	return MenuState::GameOver;
}


bool GameOverMenu::open(const uint8 index)
{
	if (isActive())
	{
		return false;
	}
	if (m_stopwatch.isRunning())
	{
		return false;
	}

	m_active = true;
	m_index = index;

	m_retrying = false;

	m_stopwatch.restart();

	return true;
}

bool GameOverMenu::open()
{
	if (isActive())
	{
		return false;
	}
	if (m_stopwatch.isRunning())
	{
		return false;
	}

	m_active = true;

	m_retrying = false;

	m_stopwatch.restart();

	return true;
}


bool GameOverMenu::apply()
{
	if (not isActive())
	{
		return false;
	}

	if (m_index == 0)
	{
		m_isClosing = true;
		m_retrying = true;

		return true;
	}
	else if (m_index == 1)
	{
		m_nextScene = State::Title;
		return true;
	}

	return false;
}


Optional<MenuRequest> GameOverMenu::request() const
{
	if (m_retrying)
	{
		return MenuRequest::Retry;
	}

	return none;
}
