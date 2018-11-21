#pragma once
#include "Singleton.h"
#include "Collider.h"

class CollisionBehaviour
{
public:
	virtual ~CollisionBehaviour() {}

public:
	virtual CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const = 0;
};

class CollisionBehaviours : public CollisionBehaviour, public Singleton<CollisionBehaviours>
{
private:
	std::unordered_map<ShapeType, std::unordered_map<ShapeType, std::unique_ptr<CollisionBehaviour>>> colliders;

private:
	friend class Singleton<CollisionBehaviours>;
	CollisionBehaviours();

public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override;
};