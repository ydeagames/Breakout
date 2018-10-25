#include "Vec2.h"
#include "MathUtils.h"
#include <cmath>

// <�x�N�g���쐬>
Vec2::Vec2(float x, float y)
	: x(x),
	y(y) {};

// <�x�N�g���̒���>
float Vec2::Length() const
{
	return std::sqrtf(LengthSquared());
}

// <�x�N�g���̒����̓��>
float Vec2::LengthSquared() const
{
	return x * x + y * y;
}

// <��������̃x�N�g���Ƃ̓���>
float Vec2::Dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}

// <��������̃x�N�g���Ƃ̊O��>
float Vec2::Cross(const Vec2& other) const
{
	return x * other.y - y * other.x;
}

// <��������̃x�N�g���Ƃ̋���>
float Vec2::LengthTo(const Vec2& other) const
{
	return std::sqrtf(LengthSquaredTo(other));
}

// <��������̃x�N�g���Ƃ̋����̓��>
float Vec2::LengthSquaredTo(const Vec2& other) const
{
	return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
}

// <���K���i������1�ɂ����j�x�N�g��>
Vec2 Vec2::Normalized() const
{
	float length = Length();
	if (length > 0)
		return{ x / length, y / length };
	return{};
}

// <���l�̃x�N�g����>
bool Vec2::Equals(const Vec2& other, float epsilon) const
{
	return fabsf(x - other.x) < epsilon && fabsf(y - other.y) < epsilon;
}

// <0�x�N�g����>
bool Vec2::IsZero() const
{
	return Equals({});
}

// <�x�N�g���̊p�x>
float Vec2::Angle() const
{
	return atan2f(y, x);
}

// <�x�N�g���̊p�x���Z>
Vec2 Vec2::Rotate(float rot) const
{
	float scale = Length();
	float angle = Angle();
	return{ std::cosf(angle + rot)*scale, std::sinf(angle + rot)*scale };
}

// <�x�N�g���𕪉�>
void Vec2::Decompose(const Vec2& angle, Vec2& vec_a, Vec2& vec_b) const
{
	float angle_rota = angle.Angle();
	float vec_rota = Angle();
	float diff_rota = vec_rota - angle_rota;
	float vec_length = Length();

	float vec_a_length = vec_length * cosf(diff_rota);
	float vec_b_length = vec_length * sinf(diff_rota);
	float vec_a_rota = angle_rota;
	float vec_b_rota = angle_rota + MathUtils::ToRadians(90);

	vec_a = { vec_a_length * std::cosf(vec_a_rota), vec_a_length * std::sinf(vec_a_rota) };
	vec_b = { vec_b_length * std::cosf(vec_b_rota), vec_b_length * std::sinf(vec_b_rota) };
}

// <�x�N�g���͂��̂܂�>
Vec2 Vec2::operator +() const
{
	return *this;
}

// <�x�N�g���𔽓]>
Vec2 Vec2::operator -() const
{
	return *this*-1;
}

// <�x�N�g�������Z>
Vec2 Vec2::operator +(const Vec2& other) const
{
	return{ x + other.x, y + other.y };
}

// <�x�N�g�������Z>
Vec2 Vec2::operator -(const Vec2& other) const
{
	return{ x - other.x, y - other.y };
}

// <�x�N�g�����X�P�[��>
Vec2 Vec2::operator *(float scale) const
{
	return{ x * scale, y * scale };
}

// <�x�N�g�����X�P�[��>
Vec2 Vec2::operator /(float scale) const
{
	if (scale == 0)
		return{};
	return{ x / scale, y / scale };
}

// <����������Z +=>
Vec2& Vec2::operator +=(const Vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

// <����������Z -=>
Vec2& Vec2::operator -=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

// <����������Z *=>
Vec2& Vec2::operator *=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

// <����������Z /=>
Vec2& Vec2::operator /=(float scale)
{
	if (scale == 0)
		*this = {};
	else
	{
		x /= scale;
		y /= scale;
	}
	return *this;
}

// <Vec2 ����ɂ��� 2�� *>
Vec2 operator *(float scale, const Vec2& vec)
{
	return{ scale * vec.x, scale * vec.y };
}

// <�x�N�g����`��>
void Vec2::Render(const Vec2& base, unsigned int color, float Thickness) const
{
	float arrow_length = 10 + Thickness * Length()*.125f;
	float arrow_rota = Angle();
	float arrow_rota1 = arrow_rota + MathUtils::ToRadians(-150);
	float arrow_rota2 = arrow_rota + MathUtils::ToRadians(150);
	DrawLineAA(base.x, base.y, base.x + x, base.y + y, color, Thickness);
	DrawLineAA(base.x + x, base.y + y, base.x + x + (arrow_length * std::cosf(arrow_rota1)), base.y + y + (arrow_length * std::sinf(arrow_rota1)), color, Thickness);
	DrawLineAA(base.x + x, base.y + y, base.x + x + (arrow_length * std::cosf(arrow_rota2)), base.y + y + (arrow_length * std::sinf(arrow_rota2)), color, Thickness);
}