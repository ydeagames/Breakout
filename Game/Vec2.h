#pragma once

// �\���̂̐錾 ============================================================

// <�x�N�g��>
class Vec2
{
public:
	static constexpr float FLOAT_EPSILON = 10e-6f;

	float x;	// X���W
	float y;	// Y���W

	// <�x�N�g���쐬>
	Vec2(float x = 0.f, float y = 0.f);

	// <�x�N�g���̒���>
	float Length() const;

	// <�x�N�g���̒����̓��>
	float LengthSquared() const;

	// <��������̃x�N�g���Ƃ̓���>
	float Dot(const Vec2& other) const;

	// <��������̃x�N�g���Ƃ̊O��>
	float Cross(const Vec2& other) const;

	// <��������̃x�N�g���Ƃ̋���>
	float LengthTo(const Vec2& other) const;

	// <��������̃x�N�g���Ƃ̋����̓��>
	float LengthSquaredTo(const Vec2& other) const;

	// <���K���i������1�ɂ����j�x�N�g��>
	Vec2 Normalized() const;

	// <���l�̃x�N�g����>
	bool Equals(const Vec2& other, float epsilon = FLOAT_EPSILON) const;

	// <0�x�N�g����>
	bool IsZero() const;

	// <�x�N�g���̊p�x>
	float Angle() const;

	// <�x�N�g���̊p�x���Z>
	Vec2 Rotate(float rot) const;

	// <�x�N�g���𕪉�>
	void Decompose(const Vec2& angle, Vec2& vec_a, Vec2& vec_b) const;

	// <�x�N�g���͂��̂܂�>
	Vec2 operator +() const;

	// <�x�N�g���𔽓]>
	Vec2 operator -() const;

	// <�x�N�g�������Z>
	Vec2 operator +(const Vec2& other) const;

	// <�x�N�g�������Z>
	Vec2 operator -(const Vec2& other) const;

	// <�x�N�g�����X�P�[��>
	Vec2 operator *(float scale) const;

	// <�x�N�g�����X�P�[��>
	Vec2 operator /(float scale) const;

	// <����������Z +=>
	Vec2& operator +=(const Vec2& other);

	// <����������Z -=>
	Vec2& operator -=(const Vec2& other);

	// <����������Z *=>
	Vec2& operator *=(float scale);

	// <����������Z /=>
	Vec2& operator /=(float scale);

	// <�x�N�g����`��>
	void Render(const Vec2& base, unsigned int color, float Thickness = 1.f) const;
};

// <Vec2 ����ɂ��� 2�� *>
Vec2 operator *(float scale, const Vec2& vec);