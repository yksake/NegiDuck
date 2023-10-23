#pragma once
#include <Siv3D.hpp>
#include "Input/InputManager.hpp"

enum class State
{
	Title,
	Game
};

struct Common
{
public:
	dss::InputManager input;


	Common();
};


using MyApp = SceneManager<State, Common>;
