#include "Paddle.h"

Paddle::Paddle(const InputButton& key_left, const InputButton& key_right) :
	m_key_left(key_left),
	m_key_right(key_right)
{
}

void Paddle::Update()
{
	Vec2 vel = {};
	if (m_key_left.GetButton())
		vel.x += -8;
	if (m_key_right.GetButton())
		vel.x += 8;
	gameObject()->GetComponent<Rigidbody>()->vel = vel;
}
//
//void Paddle::Render()
//{
//	DrawBoxAA(m_position.x - 40, m_position.y - 8, m_position.x + 40, m_position.y + 8, Colors::Yellow, true);
//}