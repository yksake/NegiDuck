#include <Siv3D.hpp> // Siv3D v0.6.12
#include "Title.hpp"
#include "Game.hpp"

void Main()
{
	Window::SetTitle(U"レンゲ背負ってやってきた！");
	Window::ResizeActual(DisplayResolution::HD_1280x720);
	Scene::SetResizeMode(ResizeMode::Actual);
	Scene::SetBackground(Color{ 34, 32, 52 });

	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.init(State::Title, 0);

	while (System::Update())
	{
		const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };

		if (not manager.update())
		{
			break;
		}
	}
}
