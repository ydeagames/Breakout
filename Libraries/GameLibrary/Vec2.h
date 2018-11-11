/**
* ベクトルクラス
*
* ベクトルの操作を提供します
*
* Copyright (c) 2018 YdeaGames
*
* This file is released under the MIT License.
* http://opensource.org/licenses/mit-license.php
*/

#pragma once

// <ベクトル>
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
	float x;	// X座標
	float y;	// Y座標

	// <ベクトル作成>
	constexpr Vec2(float x = 0.f, float y = 0.f);

	// <ベクトルの長さ>
	float Length() const;

	// <ベクトルの長さの二乗>
	constexpr float LengthSquared() const;

	// <もう一方のベクトルとの内積>
	constexpr float Dot(const Vec2& other) const;

	// <もう一方のベクトルとの外積>
	constexpr float Cross(const Vec2& other) const;

	// <もう一方のベクトルとの距離>
	float LengthTo(const Vec2& other) const;

	// <もう一方のベクトルとの距離の二乗>
	constexpr float LengthSquaredTo(const Vec2& other) const;

	// <正規化（長さを1にした）ベクトル>
	Vec2 Normalized() const;

	// <同値のベクトルか>
	constexpr bool Equals(const Vec2& other, float epsilon = FLOAT_EPSILON) const;

	// <0ベクトルか>
	constexpr bool IsZero() const;

	// <ベクトルの角度>
	float Angle() const;

	// <ベクトルの角度加算>
	Vec2 Rotate(float rot) const;

	// <ベクトルを分解>
	void Decompose(const Vec2& angle, Vec2& vec_a, Vec2& vec_b) const;

	// <ベクトルはそのまま>
	constexpr Vec2 operator +() const;

	// <ベクトルを反転>
	constexpr Vec2 operator -() const;

	// <ベクトルを加算>
	constexpr Vec2 operator +(const Vec2& other) const;

	// <ベクトルを減算>
	constexpr Vec2 operator -(const Vec2& other) const;

	// <ベクトルをスケール>
	constexpr Vec2 operator *(const Vec2& scale) const;

	// <ベクトルをスケール>
	constexpr Vec2 operator *(float scale) const;

	// <ベクトルをスケール>
	Vec2 operator /(float scale) const;

	// <複合代入演算 +=>
	Vec2& operator +=(const Vec2& other);

	// <複合代入演算 -=>
	Vec2& operator -=(const Vec2& other);

	// <複合代入演算 *=>
	Vec2& Vec2::operator *=(const Vec2& scale);
		
	// <複合代入演算 *=>
	Vec2& operator *=(float scale);

	// <複合代入演算 /=>
	Vec2& operator /=(float scale);
};

// <Vec2 が後にくる 2項 *>
constexpr Vec2 operator *(float scale, const Vec2& vec);