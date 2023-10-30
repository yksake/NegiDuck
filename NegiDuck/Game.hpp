#pragma once
#include "Common.hpp"
#include "MenuManager.hpp"
#include "RamenBowl.hpp"
#include "Duck.hpp"

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

	Texture bubble;


	void drawTime() const;
	void drawStamina() const;

	void retry();
	void changeNextStage();
};
