#include "GameObject.hpp"

GameObject::GameObject(const Vec2& pos, const SizeF& hitSize, const SizeF& viewSize)
{
	m_pos = pos;
	m_hitSize = hitSize;
	m_viewSize = viewSize;
	m_isAlive = true;
}

GameObject::GameObject(const Vec2& pos, const SizeF& size)
{
	m_pos = pos;
	m_hitSize = size;
	m_viewSize = size;
	m_isAlive = true;
}


void GameObject::moveX(const double& x)
{
	m_pos.x += x;
}

void GameObject::moveY(const double& y)
{
	m_pos.y += y;
}


bool GameObject::isHit(const GameObject& object) const
{
	return hitRegion().intersects(object.hitRegion());
}


Vec2 GameObject::pos() const
{
	return m_pos;
}

RectF GameObject::hitRegion() const
{
	const double x = m_pos.x - (m_hitSize.x / 2);
	const double y = m_pos.y - m_hitSize.y;

	return RectF{ x, y, m_hitSize };
}

RectF GameObject::viewRegion() const
{
	// viewRegion() の中央は hitRegion() の中央

	const double x = m_pos.x - (m_viewSize.x / 2);
	const double y = m_pos.y - m_viewSize.y + (m_viewSize.y - m_hitSize.y) / 2;

	return RectF{ x, y, m_viewSize };
}

double GameObject::leftX() const
{
	return hitRegion().leftX();
}

double GameObject::rightX() const
{
	return hitRegion().rightX();
}

double GameObject::topY() const
{
	return hitRegion().topY();
}

double GameObject::bottomY() const
{
	return hitRegion().bottomY();
}


bool GameObject::isAlive() const
{
	return m_isAlive;
}

void GameObject::kill()
{
	m_isAlive = false;
}
