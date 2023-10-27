#include "Game.hpp"

Game::Game(const InitData& init) : IScene(init)
{
	retry();
}

Game::~Game()
{
	
}


void Game::update()
{
	getData().input.beginFrame();
	const dss::InputState input = getData().input.inputState();

	if (menu.isActive())
	{
		if (menu.update(input))
		{
			if (const auto scene = menu.nextScene())
			{
				changeScene(scene.value(), 0);
			}
			else if (menu.isOpening())
			{
				menu.openMenu();
			}
			else if (menu.request().has_value())
			{
				if (menu.request() == MenuRequest::Retry)
				{
					menu = MenuManager{ InitType::Pause, Scene::Rect() };

					retry();
				}
				else if (menu.request() == MenuRequest::NextStage)
				{
					changeNextStage();
				}
			}
			else if (menu.isClosing())
			{
				menu.closeMenu();

				player.resume();
				bowl.resume();
			}
		}

		return;
	}
	else if (input.pauseDown)
	{
		menu.openMenu();

		player.pause();
		bowl.pause();

		return;
	}

	const bool alive = player.isAlive();

	bowl.update();

	player.update(input);

	bowl.check(player, input);

	if (alive && not player.isAlive())
	{
		menu = MenuManager{ InitType::GameOver, Scene::Rect() };
		menu.openMenu();

		return;
	}

	if (bowl.isCompleted())
	{
		menu = MenuManager{ InitType::Complete, Scene::Rect() };
		menu.openMenu();

		return;
	}
}


void Game::draw() const
{
	bowl.draw();

	player.draw();

	drawStamina();

	if (menu.isActive())
	{
		Scene::Rect().draw(Color{ 34, 32, 52, 100 });

		menu.draw();
	}
}

void Game::drawStamina() const
{
	const Vec2 pos = { 20, 30 };
	const double width = 400;
	const double height = 40;

	RectF{ pos, width, height }
		.draw(Color{ 87, 35, 0 })
		.drawFrame(0, 3, Palette::White);

	RectF{ pos, width * Clamp(player.staminaPercentage(), 0.0, 1.0), height }
		.draw(Palette::Darkturquoise);
}


void Game::retry()
{
	const Vec2 playerPos = Scene::Rect().topCenter();

	player = Duck{ playerPos };

	bowl = RamenBowl{ stageCnt, Scene::Rect().stretched(-190, -100, -10, -100) };
}

void Game::changeNextStage()
{
	stageCnt++;

	const uint8 maxStageCnt = 0;
	if (maxStageCnt < stageCnt)
	{
		changeScene(State::Result, 0);
		return;
	}

	retry();
}
