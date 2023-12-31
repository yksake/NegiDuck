﻿#pragma once
#include "SceneState.hpp"
#include "Input/InputManager.hpp"
#include "PlayTime.hpp"

struct Common
{
public:
	dss::InputManager input;

	PlayTime bestTime;
	PlayTime time;


	Common();

	void hideCursor();
};


using MyApp = SceneManager<State, Common>;
