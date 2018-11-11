/**
* �x�N�g���N���X
*
* �x�N�g���̑����񋟂��܂�
*
* Copyright (c) 2018 YdeaGames
*
* This file is released under the MIT License.
* http://opensource.org/licenses/mit-license.php
*/

#pragma once

// <�x�N�g��>
class Vec2
{
public:
	static constexpr float FLOAT_EPSILON = 10e-6f;

	static const Vec2 one;
	static const Vec2 zero;
	static const Vec2 left;
	static const Vec2 up;
	static const Vec2 right;
	static const Vec2 down;

public:
	float x;	// X���W
	float y;	// Y���W

	// <�x�N�g���쐬>
	constexpr Vec2(float x = 0.f, float y = 0.f);

	// <�x�N�g���̒���>
	float Length() const;

	// <�x�N�g���̒����̓��>
	constexpr float LengthSquared() const;

	// <��������̃x�N�g���Ƃ̓���>
	constexpr float Dot(const Vec2& other) const;

	// <��������̃x�N�g���Ƃ̊O��>
	constexpr float Cross(const Vec2& other) const;

	// <��������̃x�N�g���Ƃ̋���>
	float LengthTo(const Vec2& other) const;

	// <��������̃x�N�g���Ƃ̋����̓��>
	constexpr float LengthSquaredTo(const Vec2& other) const;

	// <���K���i������1�ɂ����j�x�N�g��>
	Vec2 Normalized() const;

	// <���l�̃x�N�g����>
	constexpr bool Equals(const Vec2& other, float epsilon = FLOAT_EPSILON) const;

	// <0�x�N�g����>
	constexpr bool IsZero() const;

	// <�x�N�g���̊p�x>
	float Angle() const;

	// <�x�N�g���̊p�x���Z>
	Vec2 Rotate(float rot) const;

	// <�x�N�g���𕪉�>
	void Decompose(const Vec2& angle, Vec2& vec_a, Vec2& vec_b) const;

	// <�x�N�g���͂��̂܂�>
	constexpr Vec2 operator +() const;

	// <�x�N�g���𔽓]>
	constexpr Vec2 operator -() const;

	// <�x�N�g�������Z>
	constexpr Vec2 operator +(const Vec2& other) const;

	// <�x�N�g�������Z>
	constexpr Vec2 operator -(const Vec2& other) const;

	// <�x�N�g�����X�P�[��>
	constexpr Vec2 operator *(const Vec2& scale) const;

	// <�x�N�g�����X�P�[��>
	constexpr Vec2 operator *(float scale) const;

	// <�x�N�g�����X�P�[��>
	Vec2 operator /(float scale) const;

	// <����������Z +=>
	Vec2& operator +=(const Vec2& other);

	// <����������Z -=>
	Vec2& operator -=(const Vec2& other);

	// <����������Z *=>
	Vec2& Vec2::operator *=(const Vec2& scale);
		
	// <����������Z *=>
	Vec2& operator *=(float scale);

	// <����������Z /=>
	Vec2& operator /=(float scale);
};

// <Vec2 ����ɂ��� 2�� *>
constexpr Vec2 operator *(float scale, const Vec2& vec);