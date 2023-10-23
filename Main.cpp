# include <Siv3D.hpp> // Siv3D v0.6.12

void Main()
{
	Window::SetTitle(U"レンゲ背負ってやってきた！");
	Window::ResizeActual(DisplayResolution::HD_1280x720);
	Scene::SetResizeMode(ResizeMode::Actual);
	Scene::SetBackground(Color{ 34, 32, 52 });

	while (System::Update())
	{
		const ScopedRenderStates2D sampler{ SamplerState::ClampNearest };
	}
}
