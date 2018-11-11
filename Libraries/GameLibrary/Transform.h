#pragma once
#include "Component.h"
#include "Vec2.h"

class Transform final : public Component
{
public:
	std::weak_ptr<Transform> parent;	// TODO �e�q����Transform
	Vec2 position;				// <�e�N�X�`��>
	float rotation;				// <��]>
	Vec2 scale;					// <�X�P�[��>

public:
	Transform(const Vec2& position, float rotation, const Vec2& scale);

	Transform();
};
