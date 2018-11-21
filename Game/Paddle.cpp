#include "Paddle.h"

Paddle::Paddle(const InputButton& key_left, const InputButton& key_right, const InputButton& key_turnleft, const InputButton& key_turnright)
	: m_key_left(key_left)
	, m_key_right(key_right)
	, m_key_turnleft(key_turnleft)
	, m_key_turnright(key_turnright)
{
}

void Paddle::Update()
{
	Vec2 vel = {};
	if (m_key_left.GetButton())
		vel.x += -8;
	if (m_key_right.GetButton())
		vel.x += 8;
	float rot = 0;
	if (m_key_turnleft.GetButton())
		rot += -MathUtils::ToRadians(8);
	if (m_key_turnright.GetButton())
		rot += MathUtils::ToRadians(8);
	gameObject()->GetComponent<Rigidbody>()->vel = vel;
	gameObject()->transform()->rotation += rot;
}
//
//void Paddle::Render()
//{
//	DrawBoxAA(m_position.x - 40, m_position.y - 8, m_position.x + 40, m_position.y + 8, Colors::Yellow, true);
//}