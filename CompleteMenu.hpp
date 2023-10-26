#pragma once
#include "AbstractMenu.hpp"

class CompleteMenu : public AbstractMenu
{
public:
	CompleteMenu(const RectF& area);
	~CompleteMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;

	Optional<MenuRequest> request() const override;


private:
	bool m_nextStage = false;
};
