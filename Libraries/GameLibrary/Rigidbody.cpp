#include "Dependencies\pch.h"
#include "Rigidbody.h"

void Rigidbody::AddForce(const Vec2& velocity)
{
	vel += velocity;
}