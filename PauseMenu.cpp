#include "PauseMenu.hpp"
#include "Font/PixelCube.hpp"

const Array<String> PauseMenu::m_Menus = {
	U"Resume",
	U"Retry",
	U"Config",
	U"Main Menu"
};


PauseMenu::PauseMenu(const RectF& area) : AbstractMenu(area)
{
	m_retrying = false;
}


bool PauseMenu::update(const dss::InputState input)
{
	if (not isActive())
	{
		return false;
	}
	if (isClosing())
	{
		return false;
	}

	if (input.pauseDown)
	{
		m_isClosing = true;
		return true;
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

void PauseMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	const uint8 fontSize = 6;

	const double interval = 100;
	Vec2 pos = m_area.center() - Vec2{0, interval * m_MaxIndex * 0.5};

	const Color defaultColor{ 128 };
	const Color selectedColor = Palette::White;

	for (uint8 i = 0; i < m_Menus.size(); i++)
	{
		Color color = defaultColor;

		if (i == m_index)
		{
			color = selectedColor;
		}

		PixelCube::Draw(m_Menus[i], fontSize, Arg::center = pos, color);

		pos.y += interval;
	}
}


MenuState PauseMenu::state() const
{
	return MenuState::Pause;
}


bool PauseMenu::open(const uint8 index)
{
	if (isActive())
	{
		return false;
	}

	m_active = true;
	m_index = index;

	m_retrying = false;

	return true;
}

bool PauseMenu::open()
{
	if (isActive())
	{
		return false;
	}

	m_active = true;

	m_retrying = false;

	return true;
}


bool PauseMenu::apply()
{
	if (not isActive())
	{
		return false;
	}

	if (m_index == 0)
	{
		m_isClosing = true;
		return true;
	}
	else if (m_index == 1)
	{
		m_isClosing = true;
		m_retrying = true;

		return true;
	}
	else if (m_index == 2)
	{
		m_nextMenu = MenuState::Config;
		return true;
	}
	else if (m_index == 3)
	{
		m_nextScene = State::Title;
		return true;
	}

	return false;
}


Optional<MenuRequest> PauseMenu::request() const
{
	if (m_retrying)
	{
		return MenuRequest::Retry;
	}

	return none;
}
