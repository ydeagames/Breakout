#pragma once
#include "Vec2.h"

class Rigidbody : public Component
{
public:
	Vec2 vel;

public:
	Rigidbody(const Vec2& vel = {})
		: vel(vel) {}

public:
	void AddForce(const Vec2& velocity);

	void Update() override;
};

