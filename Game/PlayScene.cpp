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

std::shared_ptr<Scene> PlayScene::Create()
{
	return std::make_shared<PlayScene>();
}

PlayScene::PlayScene()
	: Scene()
{
	if (auto paddle = GameObject::Create().lock())
	{
		paddle->transform()->position = { static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_BOTTOM) - 20.f };
		paddle->transform()->scale = { 80, 16 };
		paddle->AddComponent(std::make_shared<Rigidbody>());
		paddle->AddComponent(std::make_shared<Paddle>(
			InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_LEFT),
			InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_RIGHT)));
		paddle->AddComponent(std::make_shared<BoxRenderer>());
	}

	if (auto ball = GameObject::Create("Ball").lock())
	{
		ball->transform()->position = { static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) };
		ball->transform()->scale = { 5, 5 };
		ball->AddNewComponent<Rigidbody>(Vec2{ 5,5 });
		ball->AddNewComponent<Ball>();
		ball->AddNewComponent<BoxRenderer>();
		ball->AddNewComponent<Collision>(std::make_unique<Box>(Vec2{}, ball->transform()->scale));
	}

	const float width = SCREEN_WIDTH / 8;
	const float height = width / 4;

	for (int iy = 0; iy < 3; iy++)
	{
		for (int ix = 0; ix < 8; ix++)
		{
			int type = STAGE_DATA[iy][ix];
			if (type != 0)
			{
				if (auto block = GameObject::Create().lock())
				{
					block->transform()->position = { ix * width + width / 2, iy * height + height / 2 };
					block->transform()->scale = { width, height };
					block->AddComponent(std::make_shared<Block>());
					auto renderer = std::make_shared<BoxRenderer>();
					renderer->material = Material{}.SetBorder(Block::COLORS[type]);
					block->AddComponent(renderer);
					auto collision = std::make_shared<Collision>(std::make_unique<Box>(Vec2{}, block->transform()->scale));
					block->AddComponent(collision);

					class BlockBehaviour : public Component
					{
						std::weak_ptr<GameObject> ball;

						void Start()
						{
							ball = gameObject().Find("Ball");
						}

						void Update()
						{
							if (auto ball0 = ball.lock())
								if (Colliders::GetInstance().IsHit(ball0->GetComponent<Collision>(), gameObject().GetComponent<Collision>()))
								{
									ball0->GetComponent<Rigidbody>()->vel *= -1;
									gameObject().Destroy();
								}
						}
					};
					block->AddNewComponent<BlockBehaviour>();
				}
			}
		}
	}
}

PlayScene::~PlayScene()
{

}

