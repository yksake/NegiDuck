#pragma once
#include "Common.hpp"
#include "Noodle.hpp"
#include "Duck.hpp"
#include "GreenOnion.hpp"

class Game : public MyApp::Scene
{
public:
	Game(const InitData& init);
	~Game();
	void update() override;
	void draw() const override;


private:
	Noodle noodle{ Scene::CenterF() + Vec2{100, 50}, SizeF{20, 100} };
	Duck player{ Scene::CenterF() };
	GreenOnion negi{ Scene::CenterF() - Vec2{200, 0} };
};
