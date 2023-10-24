﻿#pragma once
#include "GameObject.hpp"
#include "Input/InputState.hpp"

class Duck : public GameObject
{
public:
	Duck(const Vec2& pos);

	void update(const dss::InputState& input);
	void draw() const override;

	Vec2 speed() const;
	void setSpeed(const Vec2& speed);
	void setSpeedX(const double& speedX);
	void setSpeedY(const double& speedY);

	void setEnvironmentalSpeed(const Vec2& environmentalSpeed);
	void setEnvironmentalSpeedX(const double& environmentalSpeedX);
	void setEnvironmentalSpeedY(const double& environmentalSpeedY);

	bool isFloating() const;
	void diveDown();
	void floatUp();

	bool isRight() const;
	void setDirection(const bool isRight);

	Vec2 velocity() const;

	void pause() override;
	void resume() override;


private:
	static constexpr SizeF m_HitSize = { 50, 60 };
	static constexpr SizeF m_ViewSize = { 70, 70 };
	Size m_clipSize = { 12, 12 };

	uint16 m_stamina = 100;

	Vec2 m_speed = Vec2::Zero();
	Vec2 m_environmentalSpeed = Vec2::Zero();
	Vec2 m_velocity = Vec2::Zero();

	bool m_isFloating = false;
	bool m_isRight = true;

	Stopwatch m_animationTimer;


	void updateMove(const Vec2& leftStick);
};
