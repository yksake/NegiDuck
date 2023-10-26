#pragma once
#include "AbstractMenu.hpp"

class GameOverMenu : public AbstractMenu
{
public:
	GameOverMenu(const RectF& area);
	~GameOverMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	bool isActive() const override;
	MenuState state() const override;

	bool open(const uint8 index) override;
	bool open() override;

	Optional<MenuRequest> request() const override;


private:
	static constexpr uint8 m_MaxIndex = 1;
	static const Array<String> m_Menus;

	bool m_retrying = false;

	mutable Stopwatch m_stopwatch;
	static constexpr int32 m_WaitTime = 500;


	void drawTitle() const;
	void drawIndex() const;

	bool apply();
};
