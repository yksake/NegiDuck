#pragma once
#include "AbstractMenu.hpp"

class CreditsMenu : public AbstractMenu
{
public:
	CreditsMenu(const RectF& area);
	~CreditsMenu() = default;

	bool update(const dss::InputState input) override;
	void draw() const override;

	MenuState state() const override;


private:
	static const Array<String> m_Menus;
	static const String m_Version;
	static constexpr Vec2 m_BasePos = { 1110, 200 };
	static constexpr Vec2 m_VersionRelPos = { 45, 25 };
};
