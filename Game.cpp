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
	const RectF gauge = { 20, 20, 400, 40 };

	gauge
		.draw(Color{ 87, 35, 0 })
		.drawFrame(0, 3, Palette::White);

	gauge
		.stretched(0, -gauge.w * (1.0 - player.staminaPercentage()), 0, 0)
		.draw(Palette::Darkturquoise);
}
