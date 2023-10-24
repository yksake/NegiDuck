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
}


void Game::draw() const
{
	bowl.draw();

	player.draw();
}
