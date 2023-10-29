#pragma once
#include "AbstractMenu.hpp"

class ConfigMenu : public AbstractMenu
{
public:
	ConfigMenu(const RectF& area);
	~ConfigMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;


private:

};
