#include "Collider.h"

class InverseCollider final : public Collider
{
private:
	std::unique_ptr<Collider> collider;

public:
	InverseCollider(std::unique_ptr<Collider>&& collider)
		: collider(std::move(collider)) {}

public:
	bool Collide(Collision& a, Collision& b) override
	{
		return collider->Collide(b, a);
	}

	bool IsHit(const Collision& a, const Collision& b) override
	{
		return collider->IsHit(b, a);
	}
};

class BoxAndBoxCollider : public Collider
{
public:
	bool Collide(Collision& a, Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const Collision& a, const Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class BoxAndCircleCollider : public Collider
{
public:
	bool Collide(Collision& a, Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const Collision& a, const Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class BoxAndLineCollider : public Collider
{
public:
	bool Collide(Collision& a, Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const Collision& a, const Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class CircleAndCircleCollider : public Collider
{
public:
	bool Collide(Collision& a, Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const Collision& a, const Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class CircleAndLineCollider : public Collider
{
public:
	bool Collide(Collision& a, Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const Collision& a, const Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}
};


class LineAndLineCollider : public Collider
{
public:
	bool Collide(Collision& a, Collision& b) override
	{
		// TODO ŽÀ‘•
		return false;
	}

	bool IsHit(const Collision& a, const Collision& b) override
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

bool Colliders::Collide(Collision& a, Collision& b)
{
	return colliders[a.shape->GetType()][b.shape->GetType()]->Collide(a, b);
}

bool Colliders::IsHit(const Collision& a, const Collision& b)
{
	return colliders[a.shape->GetType()][b.shape->GetType()]->IsHit(a, b);
}
