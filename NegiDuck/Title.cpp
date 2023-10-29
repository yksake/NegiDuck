#include "Title.hpp"

Title::Title(const InitData& init) : IScene(init)
{
	menu.openMenu();
}

Title::~Title()
{
	
}


void Title::update()
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


void Title::draw() const
{
	menu.draw();
}
