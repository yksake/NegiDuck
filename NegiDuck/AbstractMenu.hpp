#pragma once
#include "SceneState.hpp"
#include "Input/InputState.hpp"

enum class MenuState
{
	Main,
	Config,
	Credits,
	Pause,
	GameOver,
	Complete,
	Result
};

enum class MenuRequest
{
	Retry,
	NextStage
};

class AbstractMenu
{
public:
	AbstractMenu(const RectF& area = Scene::Rect());
	virtual ~AbstractMenu() = default;

	virtual bool update(const dss::InputState input) = 0;
	virtual void draw() const = 0;

	virtual bool isActive() const;
	virtual MenuState state() const = 0;

	virtual bool open(const uint8 index);
	virtual bool open();
	virtual bool close();

	bool isClosing() const;
	Optional<MenuState> nextMenu() const;
	Optional<State> nextScene() const;
	virtual Optional<MenuRequest> request() const;


protected:
	bool m_active;
	uint8 m_index;

	bool m_isClosing;
	Optional<MenuState> m_nextMenu;
	Optional<State> m_nextScene;

	RectF m_area;
};
