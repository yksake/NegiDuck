#include "MainMenu.hpp"
#include "Font/PixelCube.hpp"

const Array<String> MainMenu::m_Menus = {
	U"Start",
	U"Config",
	U"Credits",
	U"Exit"
};


MainMenu::MainMenu(const RectF& area) : AbstractMenu(area)
{
	
}


bool MainMenu::update(const dss::InputState input)
{
	if (not isActive())
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

void MainMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	drawLogo();
	drawIndex();
}

void MainMenu::drawLogo() const
{
	if (not isActive())
	{
		return;
	}

	const Color color = Palette::White;

	const Vec2 pos = { 150, 100 };
	const double interval = 120;

	PixelCube::Draw(U"NegiDuck", 8, Arg::topLeft = pos, color);
	PixelCube::Draw(U"With Chinese Spoon", 5, Arg::topLeft = pos.movedBy(0, interval), color);
}

void MainMenu::drawIndex() const
{
	if (not isActive())
	{
		return;
	}

	const uint8 fontSize = 5;
	const Color defaultColor{ 128 };
	const Color selectedColor = Palette::White;

	Vec2 pos = { 206, 350 };
	const double interval = 80;

	for (uint8 i = 0; i < m_Menus.size(); i++)
	{
		Color color = defaultColor;

		if (i == m_index)
		{
			color = selectedColor;
		}

		PixelCube::Draw(m_Menus[i], fontSize, Arg::topLeft = pos, color);

		pos.y += interval;
	}
}


MenuState MainMenu::state() const
{
	return MenuState::Main;
}


bool MainMenu::apply()
{
	if (not isActive())
	{
		return false;
	}

	if (m_index == 0)
	{
		m_nextScene = State::Game;
		return true;
	}
	else if (m_index == 1)
	{
		m_nextMenu = MenuState::Config;
		return true;
	}
	else if (m_index == 2)
	{
		m_nextMenu = MenuState::Credits;
		return true;
	}
	else if (m_index == 3)
	{
		System::Exit();
		return true;
	}

	return false;
}
