#include "Transform.h"

Transform::Transform(const Vec2& position, float rotation, float scale)
	: position(position)
	, rotation(rotation)
	, scale(scale)
{
}

Transform::Transform()
	: Transform(Vec2{}, 0, 0)
{
}
