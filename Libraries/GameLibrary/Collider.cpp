#include "Collider.h"
#include "MathUtils.h"

std::shared_ptr<GameObject> Collider::gameObject() const
{
	return gameobject.lock();
}

Vec2 Collider::GetVelocity() const
{
	auto rigidbody = gameObject()->GetComponent<Rigidbody>();
	if (rigidbody)
		return rigidbody->vel;
	return Vec2{};
}

// Box

void BoxCollider::Apply(const CollisionResult & result) const
{
	auto transform = gameObject()->transform();
	transform->position += GetVelocity() * result.time;
	float rotate = DX_PI_F / 2 - result.normal;
	float rotate_angle = transform->rotation + rotate;
	if (sinf(rotate_angle) < 0) {
		transform->rotation = MathUtils::GetLoop(-rotate_angle - rotate, DX_TWO_PI_F);
	}
	auto rigidbody = gameObject()->GetComponent<Rigidbody>();
	if (rigidbody)
		rigidbody->vel = Vec2::right.Rotate(transform->rotation) * (1.f - result.time);
}

CollisionResult BoxCollider::Collide(const Collider& other) const
{
	return other.Collide(*this);
}

CollisionResult BoxCollider::Collide(const BoxCollider& other) const
{
	const Box& _rect1 = shape;
	const Box& _rect2 = other.shape;

#ifndef BOXROTATE
	//各頂点座標の計算
	Vec2 vertex1[4];
	Vec2 vertex2[4];
	for (int i = 0; i < 4; ++i) {
		Vec2 c = { (i == 0 || i == 3) ? -1 : 1, (i < 2) ? -1 : 1 };
		vertex1[i] = (_rect1.size / 2 * c).Rotate(_rect1.angle) + _rect1.center;
		vertex2[i] = (_rect2.size / 2 * c).Rotate(_rect2.angle) + _rect1.center;
	}

	//線分の交差判定
	float dummy;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			LineCollider line1 = { gameobject, Line{ vertex1[i], vertex1[(i + 1) % 4] } };
			LineCollider line2 = { other.gameobject, Line{ vertex2[j], vertex2[(j + 1) % 4] } };
			CollisionResult result = line1.Collide(line2);
			if (result.hit)
				return result;
		}
	}
	return{};

#else 
	//各方向の衝突するまでの時間
	float xmin, xmax, ymin, ymax;
	xmin = xmax = ymin = ymax = -1.f;
	//座標の計算
	Vec2 pos1 = *_rect1.center;
	Vec2 pos2 = *_rect2.center;
	//_rect1から見た相対速度
	Vec2 vel = *_rigid1.vel - *_rigid2.vel;

	//X方向の衝突するまでの時間
	if (!MathUtils::FloatEquals(vel.x, 0.f)) {
		xmin = ((pos2.x - _rect2.size.x / 2) - (pos1.x + _rect1.size.x / 2)) / vel.x;
		xmax = ((pos2.x + _rect2.size.x / 2) - (pos1.x - _rect1.size.x / 2)) / vel.x;
		if (vel.x < 0) {
			std::swap(xmin, xmax);
		}
	}
	//X方向の速度が0の場合
	else {
		if ((pos1.x + _rect2.size.x / 2) > (pos2.x - _rect1.size.x / 2) &&
			(pos1.x - _rect2.size.x / 2) < (pos2.x + _rect1.size.x / 2)) {
			xmin = 0.0f;
			xmax = 1.0f;
		}
	}

	//Y方向の衝突するまでの時間
	if (!MathUtils::FloatEquals(vel.y, 0.f)) {
		ymin = ((pos2.y - _rect2.size.y / 2) - (pos1.y + _rect1.size.y / 2)) / vel.y;
		ymax = ((pos2.y + _rect2.size.y / 2) - (pos1.y - _rect1.size.y / 2)) / vel.y;
		if (vel.y < 0) {
			std::swap(ymin, ymax);
		}
	}
	//Y方向の速度が0の場合
	else {
		if ((pos1.y + _rect2.size.y / 2) > (pos2.y - _rect1.size.y / 2) &&
			(pos1.y - _rect2.size.y / 2) < (pos2.y + _rect1.size.y / 2)) {
			ymin = 0.0f;
			ymax = 1.0f;
		}
	}

	//衝突判定
	if (xmin <= 1.0f && xmax >= 0.0f &&
		ymin <= 1.0f && ymax >= 0.0f &&
		xmin <= ymax && ymin <= xmax) {
		float _time;
		float _ref_normal = 0;

		//X方向が先に衝突している
		if (xmin > ymin) {
			_time = xmin;
			if (pos1.x < pos2.x) {
				_ref_normal = DX_PI_F;
			}
			else {
				_ref_normal = 0.f;
			}
		}
		//Y方向が先に衝突している
		else {
			_time = ymin;
			if (pos1.y < pos2.y) {
				_ref_normal = PI * 1.5f;
			}
			else {
				_ref_normal = PI * 0.5f;
			}
		}
		return{ true, _time, _ref_normal };
	}
	return{};
#endif
}

CollisionResult BoxCollider::Collide(const CircleCollider& other) const
{
	const Box& _rect = GetShape(*gameObject()->transform());
	const Circle& _circle = other.GetShape(*other.gameObject()->transform());
	const Rigidbody& _rigid1 = *gameObject()->GetComponent<Rigidbody>();
	const Rigidbody& _rigid2 = *other.gameObject()->GetComponent<Rigidbody>();

#ifndef CIRCLEROTATE
	//オフセットの計算
	const Vec2& rect_rotate_pos = _rect.center;
	const Vec2& circle_pos = _circle.center;

	//相対速度の計算
	Vec2 vel = *_circle.vel - *_rect_rotate.vel;

	//線分との判定用当たり判定
	CircleCollider circle(&circle_pos, Vec2(0, 0), &vel, _circle.radius);

	//各線分との衝突するまでの時間
	float t_a, t_b;
	t_a = t_b = -1.f;

	//衝突状態
	bool is_collision = false;

	//各頂点座標との距離の計算
	Vec2 vertex[4];
	float vertex_distance[4];
	int min_distance_index = 0;
	for (int i = 0; i < 4; ++i) {
		float x = _rect_rotate.width / 2.f;
		float y = _rect_rotate.height / 2.f;
		int xc = (i == 0 || i == 3) ? -1 : 1;
		int yc = (i < 2) ? -1 : 1;
		vertex[i] = Vec2::rotate(Vec2(x*xc, y*yc), *_rect_rotate.angle) + rect_rotate_pos;
		vertex_distance[i] = Vec2::distanceSquare(circle_pos, vertex[i]);
		if (vertex_distance[i] < vertex_distance[min_distance_index]) {
			min_distance_index = i;
		}
	}

	//回転矩形の左側に近い場合
	if (vertex_distance[0] < vertex_distance[1]) {
		if (collisionCircleSegment(circle, vertex[0], vertex[3], &t_a)) {
			*_time = t_a;
			*_ref_normal = *_rect_rotate.angle + PI;
			is_collision = true;
		}
	}
	//回転矩形の右側に近い場合
	else {
		if (collisionCircleSegment(circle, vertex[1], vertex[2], &t_a)) {
			*_time = t_a;
			*_ref_normal = *_rect_rotate.angle;
			is_collision = true;
		}
	}

	//回転矩形の上側に近い場合
	if (vertex_distance[1] < vertex_distance[2]) {
		if (collisionCircleSegment(circle, vertex[0], vertex[1], &t_b)) {
			if (!is_collision || t_b < t_a) {
				*_time = t_b;
				*_ref_normal = *_rect_rotate.angle + PI * 3 / 2;
				is_collision = true;
			}
		}
	}
	//回転矩形の下側に近い場合
	else {
		if (collisionCircleSegment(circle, vertex[2], vertex[3], &t_b)) {
			if (!is_collision || t_b < t_a) {
				*_time = t_b;
				*_ref_normal = *_rect_rotate.angle + PI / 2;
				is_collision = true;
			}
		}
	}

	//角に当たった場合
	if (is_collision && FloatEqual(t_a, t_b)) {
		*_ref_normal = *_rect_rotate.angle + PI * 5 / 4 + PI / 2 * min_distance_index;
	}

	return is_collision;
#else
	//オフセットの計算
	const Vec2& rect_rotate_pos = _rect.center;
	const Vec2& circle_pos = _circle.center;

	//各頂点との判定
	Vec2 vertex[4];
	for (int i = 0; i < 4; ++i) {
		Vec2 c = { (i == 0 || i == 3) ? -1 : 1, (i < 2) ? -1 : 1 };
		vertex[i] = (_rect.size / 2 * c).Rotate(_rect.angle) + rect_rotate_pos;

		CircleCollider circle1 = { gameobject, Circle{ vertex[i], _circle.size / 2 } };
		CircleCollider circle2 = { other.gameobject, Circle{ _circle.center, _circle.size / 2 } };
		CollisionResult result = circle1.Collide(circle2);
		if (result.hit)
			return result;
	}

	//各線分との判定
	for (int i = 0; i < 4; ++i) {
		Vec2 vec1 = vertex[(i + 1) % 4] - vertex[i];
		Vec2 vec2 = circle_pos - vertex[i];
		Vec2 vec3 = circle_pos - vertex[(i + 1) % 4];
		float cross = vec2.Cross(vec1);
		float d = cross * cross / vec1.Length();
		if (d <= _circle.size*_circle.size) {
			if (vec2.Dot(vec1)*vec3.Dot(vec1) < 0) {
				return true;
			}
		}
	}

	//内外判定
	float theta[2];
	for (int i = 0; i < 2; i++) {
		Vec2 vec1 = vertex[i * 2 + 1] - vertex[i * 2];
		Vec2 vec2 = circle_pos - vertex[i * 2];
		theta[i] = atan2f(vec1.Cross(vec2), vec1.Dot(vec2));
	}

	if (0 <= theta[0] && theta[0] <= PI / 2 &&
		0 <= theta[1] && theta[1] <= PI / 2) {
		return true;
	}

	return false;
#endif
}

CollisionResult BoxCollider::Collide(const LineCollider& other) const
{
	return CollisionResult();
}

// Circle

void CircleCollider::Apply(const CollisionResult & result) const
{
}

CollisionResult CircleCollider::Collide(const Collider& other) const
{
	return other.Collide(*this);
}

CollisionResult CircleCollider::Collide(const BoxCollider& other) const
{
	return other.Collide(*this);
}

CollisionResult CircleCollider::Collide(const CircleCollider& other) const
{
	return CollisionResult();
}

CollisionResult CircleCollider::Collide(const LineCollider& other) const
{
	return CollisionResult();
}

// Line

void LineCollider::Apply(const CollisionResult & result) const
{
}

CollisionResult LineCollider::Collide(const Collider& other) const
{
	return other.Collide(*this);
}

CollisionResult LineCollider::Collide(const BoxCollider& other) const
{
	return other.Collide(*this);
}

CollisionResult LineCollider::Collide(const CircleCollider& other) const
{
	return other.Collide(*this);
}

CollisionResult LineCollider::Collide(const LineCollider& other) const
{
	return CollisionResult();
}
