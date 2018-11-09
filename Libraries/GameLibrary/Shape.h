#pragma once
#include "Vec2.h"

// <���ʒu�֌W>
enum class HorizontalSide
{
	NONE,
	CENTER,						// X����
	LEFT,						// ��
	RIGHT,						// �E
};

// <�c�ʒu�֌W>
enum class VerticalSide
{
	NONE,
	CENTER,						// Y����
	TOP,						// ��
	BOTTOM,						// ��
};

// <���̈ʒu> 
enum class Edge
{
	CENTER,						// ���̏�
	OUTER,						// ���̊O��
	INNER,						// ���̓���
};

// <���[���h�̂Ȃ���>
enum class Connection
{
	NONE,						// �q����Ȃ��A�����Ȃ���ԂɈړ�
	BARRIER,					// �ǂ�����A�i�߂Ȃ�
	LOOP,						// ���Α�����o�Ă���
};

// <�I�u�W�F�N�g�̌`>
enum class ShapeType
{
	BOX,						// �����`
	CIRCLE,						// �~
	LINE,						// ��
};

// �`
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

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	virtual float OffsetX(HorizontalSide side, float pos = 0.f, float margin = 0.f) const = 0;

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	virtual float OffsetY(VerticalSide side, float pos = 0.f, float margin = 0.f) const = 0;

	// <�I�u�W�F�N�gX�ʒu�Q�b�g>
	virtual float GetX(HorizontalSide side, float margin = 0.f) const = 0;

	// <�I�u�W�F�N�gY�ʒu�Q�b�g>
	virtual float GetY(VerticalSide side, float margin = 0.f) const = 0;

	// <�㉺�Փˏ���>
	virtual VerticalSide CollisionVertical(const Rect& obj, Connection connection, Edge edge) = 0;

	// <���E�Փˏ���>
	virtual HorizontalSide CollisionHorizontal(const Rect& obj, Connection connection, Edge edge) = 0;
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
	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetX(HorizontalSide side, float pos = 0.f, float margin = 0.f) const override;

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetY(VerticalSide side, float pos = 0.f, float margin = 0.f) const override;

	// <�I�u�W�F�N�gX�ʒu�Q�b�g>
	float GetX(HorizontalSide side, float margin = 0.f) const override;

	// <�I�u�W�F�N�gY�ʒu�Q�b�g>
	float GetY(VerticalSide side, float margin = 0.f) const override;

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetRawX(HorizontalSide side, float pos, float padding = 0.f) const;

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetRawY(VerticalSide side, float pos, float padding = 0.f) const;

	// <�I�u�W�F�N�gX�ʒu�Q�b�g>
	float GetRawX(HorizontalSide side, float padding = 0.f) const;

	// <�I�u�W�F�N�gY�ʒu�Q�b�g>
	float GetRawY(VerticalSide side, float padding = 0.f) const;

	// <�㉺�Փˏ���>
	VerticalSide CollisionVertical(const Rect& obj, Connection connection, Edge edge) override;

	// <���E�Փˏ���>
	HorizontalSide CollisionHorizontal(const Rect& obj, Connection connection, Edge edge) override;
};