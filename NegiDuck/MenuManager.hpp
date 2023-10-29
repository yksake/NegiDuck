#pragma once
#include "AbstractMenu.hpp"

enum class InitType
{
	Main,
	Pause,
	GameOver,
	Complete,
	Result
};

class MenuManager
{
public:
	MenuManager(const InitType& tyoe, const RectF& area);
	MenuManager(MenuManager&& manager);

	bool update(const dss::InputState input);
	void draw() const;

	bool isEmpty() const;
	bool isActive() const;
	Optional<MenuState> state() const;

	bool isOpening() const;
	bool isClosing() const;
	Optional<State> nextScene() const;
	Optional<MenuRequest> request() const;

	void openMenu();
	void closeMenu();


	MenuManager& operator =(MenuManager&& manager) = default;


private:
	Array<std::unique_ptr<AbstractMenu>> m_menus;
	RectF m_area;


	void addMenu(const MenuState& state);
};
