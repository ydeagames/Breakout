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

Scene* PlayScene::Create()
{
	return new PlayScene();
}

PlayScene::PlayScene()
	: Scene()
{
	std::unique_ptr<GameObject> paddle = std::make_unique<GameObject>();
	paddle->transform()->position = { static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_BOTTOM) - 20.f };
	paddle->transform()->scale = { 80, 16 };
	paddle->AddComponent(std::make_shared<Rigidbody>());
	paddle->AddComponent(std::make_shared<Paddle>(
		InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_LEFT),
		InputManager::GetInstance().GetInput<JoypadInput>()->GetInputButton(PAD_INPUT_RIGHT)));
	paddle->AddComponent(std::make_shared<BoxRenderer>());

	std::unique_ptr<GameObject> ball = std::make_unique<GameObject>();
	ball->transform()->position = { static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) };
	ball->transform()->scale = { 5, 5 };
	ball->AddComponent(std::make_shared<Rigidbody>(Vec2{ 5,5 }));
	ball->AddComponent(std::make_shared<Ball>());
	ball->AddComponent(std::make_shared<BoxRenderer>());
	auto collision = std::make_shared<Collision>(std::make_unique<Box>(Vec2{}, ball->transform()->scale));
	ball->AddComponent(collision);


	const float width = SCREEN_WIDTH / 8;
	const float height = width / 4;

	for (int iy = 0; iy < 3; iy++)
	{
		for (int ix = 0; ix < 8; ix++)
		{
			int type = STAGE_DATA[iy][ix];
			if (type != 0)
			{
				std::unique_ptr<GameObject> block = std::make_unique<GameObject>();

				block->transform()->position = { ix * width + width / 2, iy * height + height / 2 };
				block->transform()->scale = { width, height };
				block->AddComponent(std::make_shared<Block>());
				auto renderer = std::make_shared<BoxRenderer>();
				renderer->material = Material{}.SetBorder(Block::COLORS[type]);
				block->AddComponent(renderer);
				auto collision = std::make_shared<Collision>(std::make_unique<Box>(Vec2{}, block->transform()->scale));
				block->AddComponent(collision);

				m_blocks.emplace_back(std::move(block));
			}
		}
	}
}

PlayScene::~PlayScene()
{

}

void PlayScene::Update()
{
	m_paddle->Update();
	m_ball->Update();

	for (auto itr = m_blocks.begin(); itr != m_blocks.end();)
	{
		if (Colliders::GetInstance().IsHit(m_ball->GetComponent<Collision>(), (*itr)->GetComponent<Collision>()))
		{
			m_ball->GetComponent<Rigidbody>()->vel *= -1;
			itr = m_blocks.erase(itr);
			continue;
		}
		++itr;
	}
}

void PlayScene::Render()
{
	m_paddle->Render();

	for (auto itr = m_blocks.begin(); itr != m_blocks.end(); ++itr) {
		(*itr)->Render();
	}

	m_ball->Render();
}
