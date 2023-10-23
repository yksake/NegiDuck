#pragma once
#include <Siv3D.hpp>

enum class State
{
	Title,
	Game
};

struct Common
{
public:
	Common();
};


using MyApp = SceneManager<State, Common>;
