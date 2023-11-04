#pragma once
#include "Common.hpp"
#include "MenuManager.hpp"

class Title : public MyApp::Scene
{
public:
	Title(const InitData& init);
	~Title();
	void update() override;
	void draw() const override;


private:
	MenuManager menu{ InitType::Main, Scene::Rect() };

	AsyncTask<void> task;
};
