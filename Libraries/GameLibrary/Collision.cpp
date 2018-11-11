#include "Collision.h"
#include "GameObject.h"
#include "Rigidbody.h"

Vec2& Collision::GetVelocity()
{
	return gameObject->GetComponent<Rigidbody>()->vel;
}