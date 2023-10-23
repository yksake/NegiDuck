#pragma once
#include "Common.hpp"
#include "Duck.hpp"

class Game : public MyApp::Scene
{
public:
	Game(const InitData& init);
	~Game();
	void update() override;
	void draw() const override;


private:
	Duck player{ Scene::CenterF() };
};
