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

// <上下衝突処理>
VerticalSide Dimension::CollisionVertical(const Rect& field, Connection connection, Edge edge)
{
	// ヒットサイド
	VerticalSide side_hit = VerticalSide::NONE;

	// コウラ・上下壁当たり判定
	{
		// 縁に応じてパディングを調整
		float padding_top = field.GetY(VerticalSide::TOP);
		float padding_bottom = field.GetY(VerticalSide::BOTTOM);
		switch (edge)
		{
		case Edge::INNER:
			padding_top = OffsetY(VerticalSide::BOTTOM, padding_top);
			padding_bottom = OffsetY(VerticalSide::TOP, padding_bottom);
			break;
		case Edge::OUTER:
			padding_top = OffsetY(VerticalSide::TOP, padding_top);
			padding_bottom = OffsetY(VerticalSide::BOTTOM, padding_bottom);
			break;
		}

		// 当たり判定
		if (pos.y < padding_top)
			side_hit = VerticalSide::TOP;
		else if (padding_bottom <= pos.y)
			side_hit = VerticalSide::BOTTOM;

		// フィールドのつながり
		switch (connection)
		{
		case Connection::BARRIER:
			// 壁にあたったら調整
			pos.y = GetClamp(pos.y, padding_top, padding_bottom);
			break;
		case Connection::LOOP:
			// 壁にあたったらループ
			pos.y = GetLoopRange(pos.y, padding_top, padding_bottom);
			break;
		}
	}

	return side_hit;
}

// <左右衝突処理>
HorizontalSide Dimension::CollisionHorizontal(const Rect& field, Connection connection, Edge edge)
{
	// ヒットサイド
	HorizontalSide side_hit = HorizontalSide::NONE;

	// コウラ・左右壁当たり判定
	{
		// 縁に応じてパディングを調整
		float padding_left = field.GetX(HorizontalSide::LEFT);
		float padding_right = field.GetX(HorizontalSide::RIGHT);
		switch (edge)
		{
		case Edge::INNER:
			padding_left = OffsetX(HorizontalSide::RIGHT, padding_left);
			padding_right = OffsetX(HorizontalSide::LEFT, padding_right);
			break;
		case Edge::OUTER:
			padding_left = OffsetX(HorizontalSide::LEFT, padding_left);
			padding_right = OffsetX(HorizontalSide::RIGHT, padding_right);
			break;
		}

		// 当たり判定
		if (pos.x < padding_left)
			side_hit = HorizontalSide::LEFT;
		else if (padding_right <= pos.x)
			side_hit = HorizontalSide::RIGHT;

		// フィールドのつながり
		switch (connection)
		{
		case Connection::BARRIER:
			// 壁にあたったら調整
			pos.x = GetClamp(pos.x, padding_left, padding_right);
			break;
		case Connection::LOOP:
			// 壁にあたったらループ
			pos.x = GetLoopRange(pos.x, padding_left, padding_right);
			break;
		}
	}

	return side_hit;
}
