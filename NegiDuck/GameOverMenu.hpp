#pragma once
#include "AbstractMenu.hpp"

class GameOverMenu : public AbstractMenu
{
public:
	GameOverMenu(const RectF& area);
	~GameOverMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;

	Optional<MenuRequest> request() const override;


private:
	static constexpr uint8 m_MaxIndex = 1;
	static const Array<String> m_Menus;

	bool m_retrying = false;


	void drawTitle() const;
	void drawIndex() const;

	bool apply();
};
