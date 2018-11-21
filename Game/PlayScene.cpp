#include "PlayScene.h"
#include "GameMain.h"
#include "Paddle.h"
#include "Block.h"
#include "Ball.h"
// <ƒV[ƒ“>

const int PlayScene::STAGE_DATA[3][8] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3 },
};

PlayScene::PlayScene()
	: Scene()
{
	{
		auto paddle = GameObject::Create("Paddle", 3);
		paddle->transform()->position = { SCREEN.GetX(HorizontalSide::CENTER), SCREEN.GetY(VerticalSide::BOTTOM) - 20.f };
		paddle->transform()->scale = { 80, 16 };
		paddle->AddNewComponent<Rigidbody>();
		paddle->AddNewComponent<Paddle>(
			InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_LEFT),
			InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_RIGHT),
			InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_1),
			InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_2)
			);
		paddle->AddNewComponent<BoxRenderer>();
		paddle->AddNewComponentAs<Collider, BoxCollider>(Box{ Vec2{}, paddle->transform()->scale }, false);
	}

	{
		auto ball = GameObject::Create("Ball", 2);
		ball->transform()->position = SCREEN.GetCenter();
		ball->transform()->scale = { 5, 5 };
		ball->AddNewComponent<Rigidbody>(Vec2{ 5,5 }, std::vector<int>{ {1, 3} });
		ball->AddNewComponent<Ball>();
		ball->AddNewComponent<CircleRenderer>();
		ball->AddNewComponentAs<Collider, CircleCollider>(Circle{ Vec2{}, ball->transform()->scale.x }, false);
	}

	{
		const float width = SCREEN.GetSize().x / 8;
		const float height = width / 4;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 8; ix++)
			{
				int type = STAGE_DATA[iy][ix];
				if (type != 0)
				{
					auto block = GameObject::Create("Block", 1);
					block->transform()->scale = { width, height };
					block->AddNewComponent<Block>();
					block->AddNewComponentAs<Collider, BoxCollider>(Box{ Vec2{}, block->transform()->scale }, false);
					class BlockBehaviour : public CollisionEvent
					{
						void OnCollisionEnter(GameObject& other)
						{
							gameObject()->Destroy();
						}
					};
					block->AddNewComponentAs<CollisionEvent, BlockBehaviour>();

					block->transform()->position = { ix * width + width / 2, iy * height + height / 2 };
					auto renderer = std::make_shared<BoxRenderer>();
					renderer->material = Material{}.SetBorder(Block::COLORS[type]);
					block->AddComponent(renderer);
				}
			}
		}
	}
}

PlayScene::~PlayScene()
{

}

