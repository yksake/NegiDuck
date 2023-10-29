#include "CreditsMenu.hpp"
#include "Font/PixelCube.hpp"

const Array<String> CreditsMenu::m_Menus = {
	U"@Developed by",
	U"Dessert Seed Studio",
	U"",
	U"@Programming and Graphic",
	U"LargeC"
};

const String CreditsMenu::m_Version = U"r3";
const Vec2 CreditsMenu::m_BasePos = { 1110, 160 };
const Vec2 CreditsMenu::m_VersionRelPos = { 45, 25 };


CreditsMenu::CreditsMenu(const RectF& area) : AbstractMenu(area)
{

}


bool CreditsMenu::update(const dss::InputState input)
{
	if (not isActive())
	{
		return false;
	}
	if (isClosing())
	{
		return false;
	}

	bool updated = false;

	if (input.applyDown)
	{
		m_isClosing = true;
		updated = true;
	}
	if (input.cancelDown)
	{
		m_isClosing = true;
		updated = true;
	}

	return updated;
}

void CreditsMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	Vec2 pos = m_BasePos;

	for (const auto& menu : m_Menus)
	{
		if (menu.starts_with(U"@"))
		{
			String text = menu;
			const uint8 fontSize = 4;
			const Color color{ 128 };
			const double interval = 65;

			text.pop_front();

			PixelCube::Draw(text, fontSize, Arg::topRight = pos, color);

			pos.y += interval;
		}
		else if (menu.isEmpty())
		{
			const double interval = 60;

			pos.y += interval;
		}
		else
		{
			const uint8 fontSize = 6;
			const Color color = Palette::White;
			const double interval = 90;

			PixelCube::Draw(menu, fontSize, Arg::topRight = pos, color);

			pos.y += interval;
		}
	}

	// Version
	{
		const uint8 fontSize = 4;
		const Vec2 versionPos = Scene::Size() - m_VersionRelPos;
		const Color color{ 128 };

		PixelCube::Draw(m_Version, fontSize, Arg::bottomRight = versionPos, color);
	}
}


MenuState CreditsMenu::state() const
{
	return MenuState::Credits;
}
