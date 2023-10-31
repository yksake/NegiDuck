#include "Game.hpp"
#include "Font/PixelCube.hpp"

Game::Game(const InitData& init) : IScene(init)
{
	Scene::SetBackground(Palette::White);

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
				return;
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

				return;
			}
		}
		else
		{
			return;
		}
	}
	else if (input.pauseDown)
	{
		menu.openMenu();

		player.pause();
		bowl.pause();

		return;
	}

	bowl.update();

	player.update(input);

	bowl.check(player, input);

	if (not player.isAlive())
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

	drawTime();
	stamina.draw(player.staminaPercentage());

	if (menu.isActive())
	{
		Scene::Rect().draw(Color{ 34, 32, 52, 100 });

		menu.draw();
	}
}

void Game::drawTime() const
{
	const uint8 fontSize = 5;
	const Color color{ 50 };

	// minute
	{
		const Vec2 pos = { 630, 45 };

		PixelCube::Draw(U"00", fontSize, Arg::topRight = pos, color);
	}

	// colon
	{
		const Vec2 pos = { 635, 45 };

		PixelCube::Draw(U":", fontSize, pos, color);
	}

	// seconds
	{
		const Vec2 pos = { 650, 45 };

		PixelCube::Draw(U"00", fontSize, pos, color);
	}
}


void Game::retry()
{
	const Vec2 playerPos = Scene::Rect().topCenter();

	player = Duck{ playerPos };

	bowl = RamenBowl{ stageCnt, Scene::Rect().stretched(-185, -80, 0, -80) };
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
