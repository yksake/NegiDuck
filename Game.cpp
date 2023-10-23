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
	player.moveY(player.velocity().y);
}


void Game::draw() const
{
	player.draw();
}
