#include "Ball.h"
#include "GameMain.h"

Ball::Ball()
{
}

void Ball::Update()
{
	auto transform = gameObject()->transform();
	auto rigidbody = gameObject()->GetComponent<Rigidbody>();

	Bounds rect = { transform->position, transform->scale };
	if (rect.CollisionHorizontal(SCREEN, Connection::BARRIER, Edge::INNER) != HorizontalSide::NONE)
		rigidbody->vel.x *= -1;
	if (rect.CollisionVertical(SCREEN, Connection::BARRIER, Edge::INNER) != VerticalSide::NONE)
		rigidbody->vel.y *= -1;
	transform->position = rect.GetCenter();
	transform->scale = rect.GetSize();
}
