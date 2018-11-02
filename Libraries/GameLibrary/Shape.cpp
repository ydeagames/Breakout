#include "Shape.h"
#include "MathUtils.h"

using namespace MathUtils;

Dimension::Dimension(const Vec2& pos, const Vec2& size) :
	pos(pos),
	size(size)
{
}

// <オブジェクトXオフセット>
float Dimension::OffsetX(HorizontalSide side, float pos, float padding) const
{
	float offset = 0;
	switch (side)
	{
	case HorizontalSide::LEFT:
		offset = -(padding + GetAbs(size.x) / 2.f);
		break;
	case HorizontalSide::RIGHT:
		offset = (padding + GetAbs(size.x) / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトXオフセット>
float Dimension::OffsetY(VerticalSide side, float pos, float padding) const
{
	float offset = 0;
	switch (side)
	{
	case VerticalSide::TOP:
		offset = -(padding + GetAbs(size.y) / 2.f);
		break;
	case VerticalSide::BOTTOM:
		offset = (padding + GetAbs(size.y) / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトX位置ゲット>
float Dimension::GetX(HorizontalSide side, float padding) const
{
	return OffsetX(side, pos.x, padding);
}

// <オブジェクトY位置ゲット>
float Dimension::GetY(VerticalSide side, float padding) const
{
	return OffsetY(side, pos.y, padding);
}

// <オブジェクトXオフセット>
float Dimension::OffsetRawX(HorizontalSide side, float pos, float padding) const
{
	float offset = 0;
	switch (side)
	{
	case HorizontalSide::LEFT:
		offset = -(padding + size.x / 2.f);
		break;
	case HorizontalSide::RIGHT:
		offset = (padding + size.x / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトXオフセット>
float Dimension::OffsetRawY(VerticalSide side, float pos, float padding) const
{
	float offset = 0;
	switch (side)
	{
	case VerticalSide::TOP:
		offset = -(padding + size.y / 2.f);
		break;
	case VerticalSide::BOTTOM:
		offset = (padding + size.y / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトX位置ゲット>
float Dimension::GetRawX(HorizontalSide side, float padding) const
{
	return OffsetRawX(side, pos.x, padding);
}

// <オブジェクトY位置ゲット>
float Dimension::GetRawY(VerticalSide side, float padding) const
{
	return OffsetRawY(side, pos.y, padding);
}
