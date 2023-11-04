#include "Title.hpp"

Title::Title(const InitData& init) : IScene(init)
{
	auto load = [this]()
	{
		Scene::SetBackground(Color{ 34, 32, 52 });

		menu.openMenu();
	};

	task = Async(load);
}

Title::~Title()
{
	
}


void Title::update()
{
	getData().hideCursor();
	getData().input.beginFrame();

	if (task.isReady())
	{
		task.get();
	}
	else if (task.isValid())
	{
		return;
	}

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
	if (task.isValid())
	{
		Scene::Rect().draw(Color{ 34, 32, 52 });
		return;
	}

	menu.draw();
}
