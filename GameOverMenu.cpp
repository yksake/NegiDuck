#include "GameOverMenu.hpp"
#include "Font/PixelCube.hpp"

const Array<String> GameOverMenu::m_Menus = {
	U"Retry",
	U"Main Menu"
};


GameOverMenu::GameOverMenu(const RectF& area) : AbstractMenu(area)
{
	
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
	}
	if (input.downDown && m_index < m_MaxIndex)
	{
		m_index++;
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
	const uint8 fontSize = 8;
	const Vec2 pos = m_area.center();
	const Color color = Palette::White;

	PixelCube::Draw(title, fontSize, Arg::bottomCenter = pos, color);
}

void GameOverMenu::drawIndex() const
{
	if (not isActive())
	{
		return;
	}

	const uint8 fontSize = 6;
	const Color defaultColor{ 128 };
	const Color selectedColor = Palette::White;

	const double interval = 100;

	Vec2 pos = m_area.center();
	pos.y += interval * 0.75;

	for (uint8 i = 0; i < m_Menus.size(); i++)
	{
		Color color = defaultColor;

		if (i == m_index)
		{
			color = selectedColor;
		}

		PixelCube::Draw(m_Menus[i], fontSize, Arg::topCenter = pos, color);

		pos.y += interval;
	}
}


MenuState GameOverMenu::state() const
{
	return MenuState::GameOver;
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
