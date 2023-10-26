#include "ConfigMenu.hpp"
#include "Font/PixelChicken.hpp"

ConfigMenu::ConfigMenu(const RectF& area) : AbstractMenu(area)
{

}


bool ConfigMenu::update(const dss::InputState input)
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

void ConfigMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	const Color color = Palette::White;

	{
		const String text = U"This is Config";
		const uint8 fontSize = 2;
		const Vec2 pos = m_area.center() - Vec2{ 0, 60 };

		PixelChicken::Draw(text, fontSize, Arg::center = pos, color);
	}

	{
		const String text = U"COMING SOON";
		const uint8 fontSize = 3;
		const Vec2 pos = m_area.center() + Vec2{ 0, 50 };

		PixelChicken::Draw(text, fontSize, Arg::center = pos, color);
	}
}


MenuState ConfigMenu::state() const
{
	return MenuState::Config;
}
