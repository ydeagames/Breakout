#pragma once
#include "Component.h"
#include "Shape.h"
#include "Transform.h"

class CollisionResult
{
public:
	bool hit;
	float time;
	float normal;

public:
	CollisionResult(bool hit, float time, float normal)
		: hit(hit)
		, time(time)
		, normal(normal) {}

	CollisionResult()
		: CollisionResult(false, 0, 0) {}
};

class Collider;

class Collision : public Component
{
private:
	ShapeType type;
	std::unique_ptr<Collider> collider;

public:
	Collision(ShapeType type, std::unique_ptr<Collider>&& collider)
		: type(type)
		, collider(std::move(collider)) {}
	virtual ~Collision() = default;

public:
	inline ShapeType GetType() const
	{
		return type;
	}
};

class BoxCollider;
class CircleCollider;
class LineCollider;

class Collider
{
public:
	const std::weak_ptr<GameObject>& gameobject;

public:
	Collider(const std::weak_ptr<GameObject>& gameObject)
		: gameobject(gameObject) {}
	~Collider() = default;

public:
	std::shared_ptr<GameObject> gameObject() const;

public:
	virtual ShapeType GetType() const = 0;
	virtual Vec2 GetVelocity() const;
	virtual void Apply(const CollisionResult& result) const = 0;

public:
	virtual CollisionResult Collide(const Collider& other) const = 0;
	virtual CollisionResult Collide(const BoxCollider& other) const = 0;
	virtual CollisionResult Collide(const CircleCollider& other) const = 0;
	virtual CollisionResult Collide(const LineCollider& other) const = 0;
};

template <class T>
class AbstractCollider : public Collider
{
public:
	T shape;

public:
	AbstractCollider(const std::weak_ptr<GameObject>& gameObject, const T& shape)
		: Collider(gameObject)
		, shape(shape) {}
	~AbstractCollider() = default;

	virtual ShapeType GetType() const
	{
		return shape.GetType();
	}

	virtual T GetShape(const Transform& transform) const
	{
		return shape.Transformed(transform);
	}
};

class BoxCollider final : public AbstractCollider<Box>
{
public:
	BoxCollider(const std::weak_ptr<GameObject>& gameObject, const Box& shape)
		: AbstractCollider(gameObject, shape) {}

public:
	void Apply(const CollisionResult& result) const override;

public:
	CollisionResult Collide(const Collider& other) const override;
	CollisionResult Collide(const BoxCollider& other) const override;
	CollisionResult Collide(const CircleCollider& other) const override;
	CollisionResult Collide(const LineCollider& other) const override;
};

class CircleCollider final : public AbstractCollider<Circle>
{
public:
	CircleCollider(const std::weak_ptr<GameObject>& gameObject, const Circle& shape)
		: AbstractCollider(gameObject, shape) {}

public:
	void Apply(const CollisionResult& result) const override;

public:
	CollisionResult Collide(const Collider& other) const override;
	CollisionResult Collide(const BoxCollider& other) const override;
	CollisionResult Collide(const CircleCollider& other) const override;
	CollisionResult Collide(const LineCollider& other) const override;
};

class LineCollider final : public AbstractCollider<Line>
{
public:
	LineCollider(const std::weak_ptr<GameObject>& gameObject, const Line& shape)
		: AbstractCollider(gameObject, shape) {}

public:
	void Apply(const CollisionResult& result) const override;

public:
	CollisionResult Collide(const Collider& other) const override;
	CollisionResult Collide(const BoxCollider& other) const override;
	CollisionResult Collide(const CircleCollider& other) const override;
	CollisionResult Collide(const LineCollider& other) const override;
};
