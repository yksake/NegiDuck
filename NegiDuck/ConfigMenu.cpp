#include "ConfigMenu.hpp"
#include "Font/PixelCube.hpp"

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

	const String text = U"COMING SOON";
	const uint8 fontSize = 8;
	const Color color = Palette::White;

	PixelCube::Draw(text, fontSize, Arg::center = m_area.center(), color);
}


MenuState ConfigMenu::state() const
{
	return MenuState::Config;
}
