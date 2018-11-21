#include "CollisionBehaviour.h"

class InverseCollisionBehaviour final : public CollisionBehaviour
{
private:
	std::unique_ptr<CollisionBehaviour> collider;

public:
	InverseCollisionBehaviour(std::unique_ptr<CollisionBehaviour>&& collider)
		: collider(std::move(collider)) {}

public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		return collider->Collide(b, a);
	}
};

class BoxAndBoxCollisionBehaviour : public CollisionBehaviour
{
public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		// TODO ŽÀ‘•
		return{};
	}
};


class BoxAndCircleCollisionBehaviour : public CollisionBehaviour
{
public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		// TODO ŽÀ‘•
		return{};
	}
};


class BoxAndLineCollisionBehaviour : public CollisionBehaviour
{
public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		// TODO ŽÀ‘•
		return{};
	}
};


class CircleAndCircleCollisionBehaviour : public CollisionBehaviour
{
public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		// TODO ŽÀ‘•
		return{};
	}
};


class CircleAndLineCollisionBehaviour : public CollisionBehaviour
{
public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		// TODO ŽÀ‘•
		return{};
	}
};


class LineAndLineCollisionBehaviour : public CollisionBehaviour
{
public:
	CollisionResult Collide(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const override
	{
		// TODO ŽÀ‘•
		return{};
	}
};

CollisionBehaviours::CollisionBehaviours()
{
	colliders[ShapeType::BOX][ShapeType::BOX] = std::make_unique<BoxAndBoxCollisionBehaviour>();
	colliders[ShapeType::BOX][ShapeType::CIRCLE] = std::make_unique<BoxAndCircleCollisionBehaviour>();
	colliders[ShapeType::BOX][ShapeType::LINE] = std::make_unique<BoxAndLineCollisionBehaviour>();
	colliders[ShapeType::CIRCLE][ShapeType::BOX] = std::make_unique<InverseCollisionBehaviour>(std::make_unique<BoxAndCircleCollisionBehaviour>());
	colliders[ShapeType::CIRCLE][ShapeType::CIRCLE] = std::make_unique<CircleAndCircleCollisionBehaviour>();
	colliders[ShapeType::CIRCLE][ShapeType::LINE] = std::make_unique<CircleAndLineCollisionBehaviour>();
	colliders[ShapeType::LINE][ShapeType::BOX] = std::make_unique<InverseCollisionBehaviour>(std::make_unique<BoxAndLineCollisionBehaviour>());
	colliders[ShapeType::LINE][ShapeType::CIRCLE] = std::make_unique<InverseCollisionBehaviour>(std::make_unique<CircleAndLineCollisionBehaviour>());
	colliders[ShapeType::LINE][ShapeType::LINE] = std::make_unique<BoxAndBoxCollisionBehaviour>();
}

CollisionResult CollisionBehaviours::Collide(const std::shared_ptr<GameObject>& ga, const std::shared_ptr<GameObject>& gb) const
{
	if (ga && gb)
	{
		auto ca = ga->GetComponent<Collision>();
		auto cb = gb->GetComponent<Collision>();
		if (ca && cb)
		{
			auto& collider = colliders[ca->GetType()][cb->GetType()];
			if (collider)
				return collider->IsHit(ga, gb);
		}
	}
	return{};
}
