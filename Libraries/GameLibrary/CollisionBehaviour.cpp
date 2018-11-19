#include "CollisionBehaviour.h"

class InverseCollisionBehaviour final : public CollisionBehaviour
{
private:
	std::unique_ptr<CollisionBehaviour> collider;

public:
	InverseCollisionBehaviour(std::unique_ptr<CollisionBehaviour>&& collider)
		: collider(std::move(collider)) {}

public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		return collider->Collide(b, a);
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		return collider->IsHit(b, a);
	}
};

class BoxAndBoxCollisionBehaviour : public CollisionBehaviour
{
public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		// TODO ŽÀ‘•
		Box& dim_a = dynamic_cast<Box&>(*a->shape);
		Box& dim_b = dynamic_cast<Box&>(*b->shape);
		Bounds bounds_a = dim_a.GetBounds().Transformed(*a->gameObject().transform());
		Bounds bounds_b = dim_b.GetBounds().Transformed(*b->gameObject().transform());
		Vec2& vel_a = a->gameObject().GetComponent<Rigidbody>()->vel;
		Vec2& vel_b = b->gameObject().GetComponent<Rigidbody>()->vel;

		float Lx1 = (bounds_b.GetX(HorizontalSide::LEFT) - bounds_a.GetSize().x) - bounds_a.GetX(HorizontalSide::LEFT);
		float Lx2 = bounds_a.GetX(HorizontalSide::RIGHT) - (bounds_b.GetX(HorizontalSide::RIGHT) - bounds_a.GetSize().x);
		float Ly1 = (bounds_b.GetY(VerticalSide::TOP) - bounds_a.GetSize().y) - bounds_a.GetY(VerticalSide::TOP);
		float Ly2 = bounds_a.GetY(VerticalSide::BOTTOM) - (bounds_b.GetY(VerticalSide::BOTTOM) - bounds_a.GetSize().y);

		float Tx1 = Lx1 / vel_a.x;
		float Tx2 = 1 - Lx2 / vel_a.x;
		float Ty1 = Ly1 / vel_a.y;
		float Ty2 = 1 - Ly2 / vel_a.y;

		bool hit = Tx1 < Ty2 && Ty1 < Tx2;

		return hit;
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		// TODO ŽÀ‘•
		Box& dim_a = dynamic_cast<Box&>(*a->shape);
		Box& dim_b = dynamic_cast<Box&>(*b->shape);
		Vec2& vel_a = a->gameObject().GetComponent<Rigidbody>()->vel;
		Vec2& vel_b = b->gameObject().GetComponent<Rigidbody>()->vel;
		Bounds bounds_a1 = { dim_a.GetBounds().GetCenter() + a->gameObject().transform()->position, dim_a.GetBounds().GetSize() };
		Bounds bounds_a2 = { bounds_a1.GetCenter() + vel_a, bounds_a1.GetSize() };
		Bounds bounds_b = { dim_b.GetBounds().GetCenter() + b->gameObject().transform()->position, dim_b.GetBounds().GetSize() };

		float Lx1 = (bounds_b.GetX(HorizontalSide::LEFT) - bounds_a1.GetSize().x) - bounds_a1.GetX(HorizontalSide::LEFT);
		float Lx2 = bounds_a2.GetX(HorizontalSide::RIGHT) - (bounds_b.GetX(HorizontalSide::RIGHT) + bounds_a1.GetSize().x);
		float Ly1 = (bounds_b.GetY(VerticalSide::TOP) - bounds_a1.GetSize().y) - bounds_a1.GetY(VerticalSide::TOP);
		float Ly2 = bounds_a2.GetY(VerticalSide::BOTTOM) - (bounds_b.GetY(VerticalSide::BOTTOM) + bounds_a1.GetSize().y);

		float Tx1 = Lx1 / vel_a.x;
		float Tx2 = 1 - Lx2 / vel_a.x;
		float Ty1 = Ly1 / vel_a.y;
		float Ty2 = 1 - Ly2 / vel_a.y;

		bool hit = Tx1 < Ty2 && Ty1 < Tx2;

		if (hit)
			return true;

		return hit;
	}
};


class BoxAndCircleCollisionBehaviour : public CollisionBehaviour
{
public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class BoxAndLineCollisionBehaviour : public CollisionBehaviour
{
public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class CircleAndCircleCollisionBehaviour : public CollisionBehaviour
{
public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class CircleAndLineCollisionBehaviour : public CollisionBehaviour
{
public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class LineAndLineCollisionBehaviour : public CollisionBehaviour
{
public:
	bool Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b) override
	{
		// TODO ŽÀ‘•
		return false;
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

bool CollisionBehaviours::Collide(const std::shared_ptr<Collider>& a, const std::shared_ptr<Collider>& b)
{
	return colliders[a->shape->GetType()][b->shape->GetType()]->Collide(a, b);
}

bool CollisionBehaviours::IsHit(const std::shared_ptr<const Collider>& a, const std::shared_ptr<const Collider>& b)
{
	if (a && b)
	{
		auto& collider = colliders[a->shape->GetType()][b->shape->GetType()];
		if (collider)
			return collider->IsHit(a, b);
	}
	return false;
}
