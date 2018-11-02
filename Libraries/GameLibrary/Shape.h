#pragma once
#include "Vec2.h"

// <横位置関係>
enum class HorizontalSide
{
	NONE,
	CENTER,						// X中央
	LEFT,						// 左
	RIGHT,						// 右
};

// <縦位置関係>
enum class VerticalSide
{
	NONE,
	CENTER,						// Y中央
	TOP,						// 上
	BOTTOM,						// 下
};

// <縁の位置> 
enum class Edge
{
	CENTER,						// 縁の上
	OUTER,						// 縁の外側
	INNER,						// 縁の内側
};

// <ワールドのつながり>
enum class Connection
{
	NONE,						// 繋がりなし、見えない空間に移動
	BARRIER,					// 壁があり、進めない
	LOOP,						// 反対側から出てくる
};

// <オブジェクトの形>
enum class ShapeType
{
	BOX,						// 長方形
	CIRCLE,						// 円
	LINE,						// 線
};

// 形
class Shape
{
public:
	virtual ~Shape() {}

public:
	virtual ShapeType GetType() const = 0;
};

class Rect : public Shape
{
public:
	virtual ~Rect() {}

public:
	inline ShapeType GetType() const override final
	{
		return ShapeType::BOX;
	}

	// <オブジェクトXオフセット>
	virtual float OffsetX(HorizontalSide side, float pos = 0.f, float margin = 0.f) const = 0;

	// <オブジェクトXオフセット>
	virtual float OffsetY(VerticalSide side, float pos = 0.f, float margin = 0.f) const = 0;

	// <オブジェクトX位置ゲット>
	virtual float GetX(HorizontalSide side, float margin = 0.f) const = 0;

	// <オブジェクトY位置ゲット>
	virtual float GetY(VerticalSide side, float margin = 0.f) const = 0;

	// <オブジェクトXオフセット>
	virtual float OffsetRawX(HorizontalSide side, float pos, float padding = 0.f) const = 0;

	// <オブジェクトXオフセット>
	virtual float OffsetRawY(VerticalSide side, float pos, float padding = 0.f) const = 0;
};

class Dimension : public Rect
{
public:
	Vec2 pos;
	Vec2 size;

public:
	Dimension(const Vec2& pos, const Vec2& size);

	virtual ~Dimension() {}

public:
	// <オブジェクトXオフセット>
	float OffsetX(HorizontalSide side, float pos = 0.f, float margin = 0.f) const override;

	// <オブジェクトXオフセット>
	float OffsetY(VerticalSide side, float pos = 0.f, float margin = 0.f) const override;

	// <オブジェクトX位置ゲット>
	float GetX(HorizontalSide side, float margin = 0.f) const override;

	// <オブジェクトY位置ゲット>
	float GetY(VerticalSide side, float margin = 0.f) const override;

	// <オブジェクトXオフセット>
	float OffsetRawX(HorizontalSide side, float pos, float padding = 0.f) const override;

	// <オブジェクトXオフセット>
	float OffsetRawY(VerticalSide side, float pos, float padding = 0.f) const override;

	// <オブジェクトX位置ゲット>
	float GetRawX(HorizontalSide side, float padding = 0.f) const;

	// <オブジェクトY位置ゲット>
	float GetRawY(VerticalSide side, float padding = 0.f) const;
};