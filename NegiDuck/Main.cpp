#include <Siv3D.hpp> // Siv3D v0.6.12
#include "Title.hpp"
#include "Game.hpp"
#include "Result.hpp"

void Main()
{
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	Window::SetTitle(U"ネギダック");
	Window::ResizeActual(DisplayResolution::HD_1280x720);

	Scene::SetResizeMode(ResizeMode::Actual);

	FontAsset::Register(U"PixelCube", 65, U"font/x7y13PixelCube.ttf", FontStyle::Bitmap);

	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.add<Result>(State::Result)
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
