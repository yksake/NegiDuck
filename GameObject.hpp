#pragma once
#include <Siv3D.hpp>

class GameObject
{
public:
	GameObject(const Vec2& pos, const SizeF& hitSize, const SizeF& viewSize);
	GameObject(const Vec2& pos, const SizeF& size);
	virtual ~GameObject() = default;

	virtual void update() = 0;
	virtual void draw() const = 0;

	void moveX(const double& x);
	void moveY(const double& y);

	bool isHit(const GameObject& object) const;

	Vec2 pos() const;
	RectF hitRegion() const;
	RectF viewRegion() const;
	double leftX() const;
	double rightX() const;
	double topY() const;
	double bottomY() const;

	bool isAlive() const;
	void kill();

	virtual void pause() = 0;
	virtual void resume() = 0;


protected:
	Texture m_texture;
	// 中央下の座標
	Vec2 m_pos;
	Vec2 m_hitSize;
	Vec2 m_viewSize;
	bool m_isAlive;
};
