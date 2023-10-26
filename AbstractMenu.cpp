#include "AbstractMenu.hpp"

AbstractMenu::AbstractMenu(const RectF& area)
{
	m_active = false;
	m_index = 0;

	m_isClosing = false;
	m_nextMenu = none;
	m_nextScene = none;

	m_area = area;
}


bool AbstractMenu::isActive() const
{
	return m_active;
}


bool AbstractMenu::open(const uint8 index)
{
	if (isActive())
	{
		return false;
	}

	m_active = true;
	m_index = index;

	return true;
}

bool AbstractMenu::open()
{
	if (isActive())
	{
		return false;
	}

	m_active = true;

	return true;
}

bool AbstractMenu::close()
{
	if (not isActive())
	{
		return false;
	}

	m_active = false;

	m_isClosing = false;
	m_nextMenu = none;
	m_nextScene = none;

	return true;
}


bool AbstractMenu::isClosing() const
{
	return m_isClosing;
}

Optional<MenuState> AbstractMenu::nextMenu() const
{
	return m_nextMenu;
}

Optional<State> AbstractMenu::nextScene() const
{
	return m_nextScene;
}

Optional<MenuRequest> AbstractMenu::request() const
{
	return none;
}
