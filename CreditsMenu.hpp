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
	static const Vec2 m_BasePos;
	static const Vec2 m_VersionRelPos;
};
