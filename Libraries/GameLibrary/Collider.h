#pragma once
#include "Singleton.h"
#include "Collision.h"

class Collider
{
public:
	virtual ~Collider() {}

public:
	virtual bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) = 0;
	virtual bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) = 0;
};

class Colliders : public Collider, public Singleton<Colliders>
{
private:
	std::unordered_map<ShapeType, std::unordered_map<ShapeType, std::unique_ptr<Collider>>> colliders;

private:
	friend class Singleton<Colliders>;
	Colliders();

public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override;
	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override;
};