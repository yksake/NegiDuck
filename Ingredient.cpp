#include "Ingredient.hpp"

Ingredient::Ingredient(const Vec2& pos, const SizeF& hitSize, const SizeF& viewSize)
	: GameObject(pos, hitSize, viewSize)
{

}

Ingredient::Ingredient(const Vec2& pos, const SizeF& size) : GameObject(pos, size)
{

}
