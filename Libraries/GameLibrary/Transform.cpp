#include "Transform.h"

Transform::Transform(const Vec2& position, float rotation, const Vec2& scale)
	: position(position)
	, rotation(rotation)
	, scale(scale)
{
}

Transform::Transform()
	: Transform(Vec2{}, 0, Vec2{ 1, 1 })
{
}
