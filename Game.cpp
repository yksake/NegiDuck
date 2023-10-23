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

	player.update(getData().input.inputState());

	player.moveX(player.velocity().x);
	noodle.hitEventLR(player);

	player.moveY(player.velocity().y);
	noodle.hitEventTB(player);

	if (negi.isHit(player))
	{
		negi.kill();
	}
}


void Game::draw() const
{
	noodle.draw();

	negi.draw();

	player.hitRegion().draw(Color{ 255, 0, 0, 100 });
	player.draw();
}
