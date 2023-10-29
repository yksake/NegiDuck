#include "MenuManager.hpp"
#include "MainMenu.hpp"
#include "ConfigMenu.hpp"
#include "CreditsMenu.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "CompleteMenu.hpp"
#include "ResultMenu.hpp"

MenuManager::MenuManager(const InitType& type, const RectF& area)
{
	m_menus.clear();
	m_area = area;

	if (type == InitType::Main)
	{
		addMenu(MenuState::Main);
	}
	else if (type == InitType::Pause)
	{
		addMenu(MenuState::Pause);
	}
	else if (type == InitType::GameOver)
	{
		addMenu(MenuState::GameOver);
	}
	else if (type == InitType::Complete)
	{
		addMenu(MenuState::Complete);
	}
	else if (type == InitType::Result)
	{
		addMenu(MenuState::Result);
	}
}

MenuManager::MenuManager(MenuManager&& manager)
{
	m_menus.clear();

	for (int i = 0; i < manager.m_menus.size(); i++)
	{
		m_menus << std::move(manager.m_menus[i]);
	}

	m_area = manager.m_area;
}


bool MenuManager::update(const dss::InputState input)
{
	if (isEmpty())
	{
		return false;
	}

	return m_menus.back()->update(input);
}

void MenuManager::draw() const
{
	if (isEmpty())
	{
		return;
	}

	m_menus.back()->draw();
}


bool MenuManager::isEmpty() const
{
	return m_menus.isEmpty();
}

bool MenuManager::isActive() const
{
	if (isEmpty())
	{
		return false;
	}

	return m_menus.back()->isActive();
}

Optional<MenuState> MenuManager::state() const
{
	if (not isActive())
	{
		return none;
	}

	return m_menus.back()->state();
}


bool MenuManager::isOpening() const
{
	if (isEmpty())
	{
		return false;
	}

	return m_menus.back()->nextMenu().has_value();
}

bool MenuManager::isClosing() const
{
	if (isEmpty())
	{
		return false;
	}

	return m_menus.back()->isClosing();
}

Optional<State> MenuManager::nextScene() const
{
	if (isEmpty())
	{
		return none;
	}

	return m_menus.back()->nextScene();
}

Optional<MenuRequest> MenuManager::request() const
{
	if (isEmpty())
	{
		return none;
	}

	return m_menus.back()->request();
}


void MenuManager::openMenu()
{
	if (isEmpty())
	{
		return;
	}

	if (const auto menuState = m_menus.back()->nextMenu())
	{
		m_menus.back()->close();

		addMenu(menuState.value());
		m_menus.back()->open(0);

		return;
	}

	if (not m_menus.back()->isActive())
	{
		m_menus.back()->open(0);
	}
}

void MenuManager::closeMenu()
{
	if (isEmpty())
	{
		return;
	}

	m_menus.back()->close();

	if (1 < m_menus.size())
	{
		m_menus.pop_back();

		m_menus.back()->open();
	}
}


void MenuManager::addMenu(const MenuState& state)
{
	if (state == MenuState::Main)
	{
		m_menus << std::make_unique<MainMenu>(m_area);
	}
	else if (state == MenuState::Config)
	{
		m_menus << std::make_unique<ConfigMenu>(m_area);
	}
	else if (state == MenuState::Credits)
	{
		m_menus << std::make_unique<CreditsMenu>(m_area);
	}
	else if (state == MenuState::Pause)
	{
		m_menus << std::make_unique<PauseMenu>(m_area);
	}
	else if (state == MenuState::GameOver)
	{
		m_menus << std::make_unique<GameOverMenu>(m_area);
	}
	else if (state == MenuState::Complete)
	{
		m_menus << std::make_unique<CompleteMenu>(m_area);
	}
	else if (state == MenuState::Result)
	{
		m_menus << std::make_unique<ResultMenu>(m_area);
	}
}
