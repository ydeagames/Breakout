#include "Rigidbody.h"
#include "Transform.h"

void Rigidbody::AddForce(const Vec2& velocity)
{
	vel += velocity;
}

void Rigidbody::Update()
{
	gameObject->transform()->position += vel;
}