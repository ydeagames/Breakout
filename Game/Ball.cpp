#include "Ball.h"

Ball::Ball()
{
}

void Ball::Update()
{
	auto transform = gameObject->transform();
	auto rigidbody = gameObject->GetComponent<Rigidbody>();

	Bounds bounds = { Vec2{320, 240}, Vec2{640, 480} };
	Bounds rect = { transform->position, transform->scale };
	if (rect.CollisionHorizontal(bounds, Connection::BARRIER, Edge::INNER) != HorizontalSide::NONE)
		rigidbody->vel.x *= -1;
	if (rect.CollisionVertical(bounds, Connection::BARRIER, Edge::INNER) != VerticalSide::NONE)
		rigidbody->vel.y *= -1;
	transform->position = rect.GetCenter();
	transform->scale = rect.GetSize();
}
