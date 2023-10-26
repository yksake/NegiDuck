#pragma once
#include "AbstractMenu.hpp"

class PauseMenu : public AbstractMenu
{
public:
	PauseMenu(const RectF& area);
	~PauseMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;

	bool open(const uint8 index) override;
	bool open() override;

	Optional<MenuRequest> request() const override;


private:
	static constexpr uint8 m_MaxIndex = 3;
	static const Array<String> m_Menus;

	bool m_retrying;


	bool apply();
};
