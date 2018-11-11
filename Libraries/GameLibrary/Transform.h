#pragma once
#include "Component.h"
#include "Vec2.h"

class Transform final : public Component
{
public:
	std::weak_ptr<Transform> parent;	// TODO 親子相対Transform
	Vec2 position;				// <テクスチャ>
	float rotation;				// <回転>
	Vec2 scale;					// <スケール>

public:
	Transform(const Vec2& position, float rotation, float scale);

	Transform();
};
