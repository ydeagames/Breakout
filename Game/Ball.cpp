#include "Ball.h"

Ball::Ball(Dimension rect) :
	rect(rect),
	vel(Vec2{10, 10})
{
}

void Ball::Update()
{
	rect.pos += vel;

	Dimension dim = { Vec2{320, 240}, Vec2{640, 480} };

	if (rect.CollisionHorizontal(dim, Connection::BARRIER, Edge::INNER) != HorizontalSide::NONE)
		vel.x *= -1;
	if (rect.CollisionVertical(dim, Connection::BARRIER, Edge::INNER) != VerticalSide::NONE)
		vel.y *= -1;
}

void Ball::Render()
{
	DrawBoxAA(rect.GetX(HorizontalSide::LEFT), rect.GetY(VerticalSide::TOP), rect.GetX(HorizontalSide::RIGHT), rect.GetY(VerticalSide::BOTTOM), Colors::White, true);
}