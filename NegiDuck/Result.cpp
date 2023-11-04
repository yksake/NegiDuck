#include "Result.hpp"
#include "Font/PixelCube.hpp"

Result::Result(const InitData& init) : IScene(init)
{
	Scene::SetBackground(Color{ 34, 32, 52 });
}

Result::~Result()
{

}


void Result::update()
{
	getData().hideCursor();
	getData().input.beginFrame();
	const auto& input = getData().input.inputState();

	if (input.applyDown)
	{
		changeScene(State::Title, 0);
	}
}

void Result::draw() const
{
	// Paper
	{
		RectF paper = Scene::Rect().stretched(-320, 0);

		paper.draw(Palette::White);
	}

	const Color color{ 50 };

	// Title
	{
		Vec2 pos = Scene::CenterF().movedBy(0, -270);

		PixelCube::Draw(U"NegiDuck", 4, Arg::center = pos, color);

		pos.y += 80;

		PixelCube::Draw(U"Result", 9, Arg::center = pos, color);
	}

	const uint8 fontSize = 5;
	const double relX = 250;
	double y = Scene::CenterF().y - 30;

	{
		PixelCube::Draw(U"1st", fontSize, Vec2{Scene::CenterF().x - relX, y}, color);

		const auto& time = getData().time;
		String s = U"{0:0>2}\'{1:0>2}\"{2:0>3}";
		String text = Fmt(s)(time.minutes.count(), time.seconds.count(), time.ms.count());

		PixelCube::Draw(text, fontSize, Arg::topRight = Vec2{Scene::CenterF().x + relX, y}, color);
	}

	y += 140;

	{
		const String line = U"----------------";
		PixelCube::Draw(line, fontSize, Arg::topCenter = Vec2{ Scene::CenterF().x, y }, color);
	}

	y += 80;

	{
		PixelCube::Draw(U"Total", fontSize, Vec2{ Scene::CenterF().x - relX, y }, color);

		const auto& total = getData().time;
		String s = U"{0:0>2}\'{1:0>2}\"{2:0>3}";
		String text = Fmt(s)(total.minutes.count(), total.seconds.count(), total.ms.count());

		PixelCube::Draw(text, fontSize, Arg::topRight = Vec2{ Scene::CenterF().x + relX, y }, color);
	}
}
