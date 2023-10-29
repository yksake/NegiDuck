#pragma once
#include "AbstractMenu.hpp"

class ResultMenu : public AbstractMenu
{
public:
	ResultMenu(const RectF& area);
	~ResultMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;
};
