#pragma once
#include "AbstractMenu.hpp"

class MainMenu : public AbstractMenu
{
public:
	MainMenu(const RectF& area);
	~MainMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;


private:
	static constexpr uint8 m_MaxIndex = 3;
	static const Array<String> m_Menus;

	static constexpr int m_BaseX = 1110;


	void drawLogo() const;
	void drawIndex() const;

	bool apply();
};
