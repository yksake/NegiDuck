#include "ResultMenu.hpp"
#include "Font/PixelCube.hpp"

ResultMenu::ResultMenu(const RectF& area) : AbstractMenu(area)
{

}


bool ResultMenu::update(const dss::InputState input)
{
	if (not isActive())
	{
		return false;
	}
	if (isClosing())
	{
		return false;
	}

	if (input.applyDown)
	{
		m_nextScene = State::Title;
		return true;
	}

	return false;
}


void ResultMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	const String text = U"Result";
	const uint8 fontSize = 8;
	const Vec2 pos = m_area.center();
	const Color color = Palette::White;

	PixelCube::Draw(text, fontSize, Arg::center = pos, color);
}


MenuState ResultMenu::state() const
{
	return MenuState::Result;
}
