#pragma once
#include "Singleton.h"
#include "Collision.h"

class Collider
{
public:
	virtual ~Collider() {}

public:
	virtual bool Collide(Collision& a, Collision& b) = 0;
	virtual bool IsHit(const Collision& a, const Collision& b) = 0;
};

class Colliders : public Collider, public Singleton<Colliders>
{
private:
	std::unordered_map<ShapeType, std::unordered_map<ShapeType, std::unique_ptr<Collider>>> colliders;

private:
	Colliders();

public:
	bool Collide(Collision& a, Collision& b) override;
	bool IsHit(const Collision& a, const Collision& b) override;
};