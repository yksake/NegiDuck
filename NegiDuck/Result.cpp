#include "Result.hpp"

Result::Result(const InitData& init) : IScene(init)
{
	menu.openMenu();
}

Result::~Result()
{

}


void Result::update()
{
	getData().input.beginFrame();

	if (menu.update(getData().input.inputState()))
	{
		if (const auto state = menu.nextScene())
		{
			changeScene(state.value(), 0);
		}
		else if (menu.isOpening())
		{
			menu.openMenu();
		}
		else if (menu.isClosing())
		{
			menu.closeMenu();
		}
	}
}

void Result::draw() const
{
	menu.draw();
}
