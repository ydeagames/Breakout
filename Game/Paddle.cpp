#include "Paddle.h"
#include "GameMain.h"

Paddle::Paddle(const Bounds& limit)
	: limit(limit)
{
}

void Paddle::Start()
{
	auto transform = gameObject()->transform();
	gameObject()->GetComponent<Rigidbody>()->hit_layers.push_back(5);
	for (int i = 0; i < 4; ++i)
	{
		Vec2 c1 = { (i == 0 || i == 3) ? -1 : 1, (i < 2) ? -1 : 1 };
		int j = (i + 1) % 4;
		Vec2 c2 = { (j == 0 || j == 3) ? -1 : 1, (j < 2) ? -1 : 1 };
		Vec2 p1 = limit.GetExtents() * c1;
		Vec2 p2 = limit.GetExtents() * c2;
		auto obj = GameObject::Create(gameObject()->name + ":Wall", 5);
		*obj->transform() = *transform;
		obj->AddNewComponentAs<Collider, LineCollider>(Line{ p1, p2 });
		auto renderer = std::make_shared<LineRenderer>();
		renderer->material = Material{}.SetBorder(Colors::White, 1.f, 2.f);
		obj->AddComponent<LineRenderer>(renderer);
	}
}

void Paddle::Update()
{
	auto& input = InputManager::GetInstance();
	auto transform = gameObject()->transform();

	Vec2 vel = {};
	if (input.joypad->GetButton(PAD_INPUT_LEFT) || input.key->GetButton(KEY_INPUT_A))
		vel.x += -8;
	if (input.joypad->GetButton(PAD_INPUT_RIGHT) || input.key->GetButton(KEY_INPUT_D))
		vel.x += 8;
	if (input.joypad->GetButton(PAD_INPUT_UP) || input.key->GetButton(KEY_INPUT_W))
		vel.y += -8;
	if (input.joypad->GetButton(PAD_INPUT_DOWN) || input.key->GetButton(KEY_INPUT_S))
		vel.y += 8;

	Vec2 mouse = input.mouse->GetPosition();
	static Vec2 lastmouse = mouse;
	Vec2 move = mouse - lastmouse;
	Bounds outer = SCREEN.Expand(Vec2{ -20, 200 });
	if (!outer.Contains(mouse))
	{
		Vec2 loop = mouse.GetLoopRange(outer.GetMin(), outer.GetMax());
		Vec2 clamp = outer.ClosestPoint(mouse);
		input.mouse->SetPosition(Vec2{ (mouse = loop).x, clamp.y });
	}
	lastmouse = mouse;
	SetMouseDispFlag(!SCREEN.Contains(mouse));

	float rot = MathUtils::ToRadians(move.x);
	if (input.key->GetButton(KEY_INPUT_Q))
		rot += -MathUtils::ToRadians(8);
	if (input.key->GetButton(KEY_INPUT_E))
		rot += MathUtils::ToRadians(8);
	gameObject()->GetComponent<Rigidbody>()->vel = vel;
	transform->rotation += rot;

	/*
	Bounds rect = { transform->position, transform->scale };
	rect.CollisionHorizontal(limit, Connection::BARRIER, Edge::INNER);
	rect.CollisionVertical(limit, Connection::BARRIER, Edge::INNER);
	transform->position = rect.GetCenter();
	transform->scale = rect.GetSize();
	*/
}

void Paddle::Render()
{
	//DrawBoxAA(limit.GetX(HorizontalSide::LEFT), limit.GetY(VerticalSide::TOP), limit.GetX(HorizontalSide::RIGHT), limit.GetY(VerticalSide::BOTTOM), Colors::Yellow, false);
}