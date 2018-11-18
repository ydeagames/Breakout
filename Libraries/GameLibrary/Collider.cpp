#include "Collider.h"

class InverseCollider final : public Collider
{
private:
	std::unique_ptr<Collider> collider;

public:
	InverseCollider(std::unique_ptr<Collider>&& collider)
		: collider(std::move(collider)) {}

public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
	{
		return collider->Collide(b, a);
	}

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
	{
		return collider->IsHit(b, a);
	}
};

class BoxAndBoxCollider : public Collider
{
public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
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

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
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


class BoxAndCircleCollider : public Collider
{
public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class BoxAndLineCollider : public Collider
{
public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class CircleAndCircleCollider : public Collider
{
public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class CircleAndLineCollider : public Collider
{
public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class LineAndLineCollider : public Collider
{
public:
	bool Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};

Colliders::Colliders()
{
	colliders[ShapeType::BOX][ShapeType::BOX] = std::make_unique<BoxAndBoxCollider>();
	colliders[ShapeType::BOX][ShapeType::CIRCLE] = std::make_unique<BoxAndCircleCollider>();
	colliders[ShapeType::BOX][ShapeType::LINE] = std::make_unique<BoxAndLineCollider>();
	colliders[ShapeType::CIRCLE][ShapeType::BOX] = std::make_unique<InverseCollider>(std::make_unique<BoxAndCircleCollider>());
	colliders[ShapeType::CIRCLE][ShapeType::CIRCLE] = std::make_unique<CircleAndCircleCollider>();
	colliders[ShapeType::CIRCLE][ShapeType::LINE] = std::make_unique<CircleAndLineCollider>();
	colliders[ShapeType::LINE][ShapeType::BOX] = std::make_unique<InverseCollider>(std::make_unique<BoxAndLineCollider>());
	colliders[ShapeType::LINE][ShapeType::CIRCLE] = std::make_unique<InverseCollider>(std::make_unique<CircleAndLineCollider>());
	colliders[ShapeType::LINE][ShapeType::LINE] = std::make_unique<BoxAndBoxCollider>();
}

bool Colliders::Collide(const std::shared_ptr<Collision>& a, const std::shared_ptr<Collision>& b)
{
	return colliders[a->shape->GetType()][b->shape->GetType()]->Collide(a, b);
}

bool Colliders::IsHit(const std::shared_ptr<const Collision>& a, const std::shared_ptr<const Collision>& b)
{
	if (a && b)
	{
		auto& collider = colliders[a->shape->GetType()][b->shape->GetType()];
		if (collider)
			return collider->IsHit(a, b);
	}
	return false;
}
