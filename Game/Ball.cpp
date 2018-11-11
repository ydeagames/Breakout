#include "Ball.h"

Ball::Ball()
{
}

void Ball::Update()
{
	auto transform = gameObject->transform();
	auto rigidbody = gameObject->GetComponent<Rigidbody>();

	Dimension dim = { Vec2{320, 240}, Vec2{640, 480} };
	Dimension rect = { transform->position, transform->scale };
	if (rect.CollisionHorizontal(dim, Connection::BARRIER, Edge::INNER) != HorizontalSide::NONE)
		rigidbody->vel.x *= -1;
	if (rect.CollisionVertical(dim, Connection::BARRIER, Edge::INNER) != VerticalSide::NONE)
		rigidbody->vel.y *= -1;
}
