#include "MainMenu.hpp"
#include "Font/PixelChicken.hpp"

const Array<String> MainMenu::m_Menus = {
	U"START",
	U"CONFIG",
	U"CREDITS",
	U"EXIT"
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

	const uint8 fontSize = 3;
	const Color color = Palette::White;

	const Vec2 towerPos = { 150, 100 };
	const Vec2 ovenPos = towerPos + Vec2{ 0, 120 };

	PixelChicken::Draw(U"NegiDuck:", 3, Arg::topLeft = towerPos, color);
	PixelChicken::Draw(U"With Chinese Spoon", 2, Arg::topLeft = ovenPos, color);
}

void MainMenu::drawIndex() const
{
	if (not isActive())
	{
		return;
	}

	const uint8 fontSize = 2;
	const Color defaultColor{ 128 };
	const Color selectedColor = Palette::White;

	Vec2 pos = { 190, 350 };
	const double interval = 70;

	for (uint8 i = 0; i < m_Menus.size(); i++)
	{
		Color color = defaultColor;

		if (i == m_index)
		{
			color = selectedColor;
		}

		PixelChicken::Draw(m_Menus[i], fontSize, Arg::topLeft = pos, color);

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
