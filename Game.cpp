#include "Game.hpp"

Game::Game(const InitData& init) : IScene(init)
{
	
}

Game::~Game()
{
	
}


void Game::update()
{
	getData().input.beginFrame();

	bowl.update();

	player.update(getData().input.inputState());

	bowl.check(player, getData().input.inputState());

	if (bowl.isCompleted())
	{
		Print << U"Bowl Completed!!!";
	}
}


void Game::draw() const
{
	bowl.draw();

	player.draw();

	drawStamina();

	FontAsset(U"font")(Format(score)).draw(Arg::topRight = Vec2{ Scene::Width() - 20, 20 }, Palette::White);
}

void Game::drawStamina() const
{
	const Vec2 pos = { 20, 20 };
	const double width = 400;
	const double height = 40;

	RectF{ pos, width, height }
		.draw(Color{ 87, 35, 0 })
		.drawFrame(0, 3, Palette::White);

	RectF{ pos, width * Clamp(player.staminaPercentage(), 0.0, 1.0), height }
		.draw(Palette::Darkturquoise);
}
