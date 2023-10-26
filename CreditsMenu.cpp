#include "CreditsMenu.hpp"
#include "Font/PixelChicken.hpp"

const Array<String> CreditsMenu::m_Menus = {
	U"@DEVELOPED BY",
	U"DESSERT SEED STUDIO",
	U"",
	U"@PROGRAMMING AND GRAPHIC",
	U"LARGE C"
};

const String CreditsMenu::m_Version = U"VERSION 2.0.0-BETA.1";


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
			const uint8 fontSize = 1;
			const Color color{ 128 };
			const double interval = 45;

			text.pop_front();

			PixelChicken::Draw(text, fontSize, Arg::topRight = pos, color);

			pos.y += interval;
		}
		else if (menu.isEmpty())
		{
			const double interval = 35;

			pos.y += interval;
		}
		else
		{
			const uint8 fontSize = 2;
			const Color color = Palette::White;
			const double interval = 90;

			PixelChicken::Draw(menu, fontSize, Arg::topRight = pos, color);

			pos.y += interval;
		}
	}

	// Version
	{
		const uint8 fontSize = 1;
		const Vec2 versionPos = Scene::Size() - m_VersionRelPos;
		const Color color{ 128 };

		PixelChicken::Draw(m_Version, fontSize, Arg::bottomRight = versionPos, color);
	}
}


MenuState CreditsMenu::state() const
{
	return MenuState::Credits;
}
