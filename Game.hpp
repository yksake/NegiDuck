#pragma once
#include "Common.hpp"
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
	RamenBowl bowl;
	Duck player{ Scene::CenterF() };

	uint8 score = 0;


	void drawStamina() const;
};
