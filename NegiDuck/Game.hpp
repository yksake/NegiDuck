#pragma once
#include "Common.hpp"
#include "MenuManager.hpp"
#include "RamenBowl.hpp"
#include "Duck.hpp"
#include "RamenTimer.hpp"
#include "StaminaGauge.hpp"

class Game : public MyApp::Scene
{
public:
	Game(const InitData& init);
	~Game();
	void update() override;
	void draw() const override;


private:
	MenuManager menu{ InitType::Pause, Scene::Rect() };

	RamenBowl bowl{ 0, Scene::Rect() };
	Duck player{ Scene::CenterF() };

	uint8 stageCnt = 0;

	RamenTimer timer{ Vec2{640, 75} };
	StaminaGauge stamina{ Vec2{20, 160} };


	void retry();
	void changeNextStage();
};
