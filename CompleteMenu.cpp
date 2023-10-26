#include "CompleteMenu.hpp"
#include "Font/PixelChicken.hpp"

CompleteMenu::CompleteMenu(const RectF& area) : AbstractMenu(area)
{

}


bool CompleteMenu::update(const dss::InputState input)
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
		m_nextStage = true;
		return true;
	}

	return false;
}

void CompleteMenu::draw() const
{
	if (not isActive())
	{
		return;
	}

	const String text = U"Completed!";
	const uint8 fontSize = 3;
	const Vec2 pos = m_area.center();
	const Color color = Palette::White;

	PixelChicken::Draw(text, fontSize, Arg::center = pos, color);
}


MenuState CompleteMenu::state() const
{
	return MenuState::Complete;
}


Optional<MenuRequest> CompleteMenu::request() const
{
	if (m_nextStage)
	{
		return MenuRequest::NextStage;
	}

	return none;
}
