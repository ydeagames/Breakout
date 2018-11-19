#pragma once
#include "Singleton.h"
#include "Collider.h"

class CollisionBehaviour
{
public:
	virtual ~CollisionBehaviour() {}

public:
	virtual bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) = 0;
	virtual bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) = 0;
};

class CollisionBehaviours : public CollisionBehaviour, public Singleton<CollisionBehaviours>
{
private:
	std::unordered_map<ShapeType, std::unordered_map<ShapeType, std::unique_ptr<CollisionBehaviour>>> colliders;

private:
	friend class Singleton<CollisionBehaviours>;
	CollisionBehaviours();

public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override;
	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override;
};