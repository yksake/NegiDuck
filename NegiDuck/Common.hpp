#pragma once
#include "SceneState.hpp"
#include "Input/InputManager.hpp"

struct Common
{
public:
	dss::InputManager input;


	Common();
};


using MyApp = SceneManager<State, Common>;
