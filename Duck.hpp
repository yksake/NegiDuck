#pragma once
#include "GameObject.hpp"
#include "Input/InputState.hpp"

class Duck : public GameObject
{
public:
	Duck(const Vec2& pos);

	void update(const dss::InputState& input);
	void draw() const override;

	void setSpeedX(const double& speedX);
	void setSpeedY(const double& speedY);

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
	static constexpr double m_MoveVelocity = 7;
	static constexpr double m_Registance = 0.95;
	Vec2 m_speed = Vec2::Zero();
	Vec2 m_velocity = Vec2::Zero();
	static constexpr double m_TerminalVelocity = 3.0;
	Vec2 m_previousVelocity = Vec2::Zero();

	bool m_isRight = true;

	Stopwatch m_animationTimer;
};
