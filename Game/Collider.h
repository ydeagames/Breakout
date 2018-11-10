#pragma once

class Collider
{
protected:
	bool trigger;

public:
	Collider(bool trigger = false);
	virtual ~Collider() {};

protected:
	virtual bool Collide(Collider& other, bool trigger) = 0;

public:
	virtual bool Collide(Collider& other) = 0;
	virtual bool IsHit(Collider& other) = 0;
};

