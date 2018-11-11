#include "GameMain.h"
#include <cmath>
#include "Paddle.h"
#include "Block.h"
#include "Ball.h"

// <GameƒNƒ‰ƒX>

const int Game::STAGE_DATA[3][8] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 3, 3, 3, 3, 3, 3, 3, 3 },
};

// ƒQ[ƒ€‚Ì‰Šú‰»ˆ—
Game::Game() :
	m_frame_timer(new FrameTimer),
	m_input(new InputManager),
	m_paddle(nullptr),
	m_ball(nullptr)
{
	m_paddle = new GameObject();
	m_paddle->transform()->position = { static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_BOTTOM) - 20.f };
	m_paddle->transform()->scale = { 80, 16 };
	m_paddle->AddComponent(std::make_shared<Rigidbody>());
	m_paddle->AddComponent(std::make_shared<Paddle>(
		m_input->GetInput<JoypadInput>("Joypad")->GetInputButton(PAD_INPUT_LEFT),
		m_input->joypad->GetInputButton(PAD_INPUT_RIGHT)));
	m_paddle->AddComponent(std::make_shared<BoxRenderer>());

	m_ball = new GameObject();
	m_ball->transform()->position = { static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) };
	m_ball->transform()->scale = { 5, 5 };
	m_ball->AddComponent(std::make_shared<Rigidbody>(Vec2{ 5,5 }));
	m_ball->AddComponent(std::make_shared<Ball>());
	m_ball->AddComponent(std::make_shared<BoxRenderer>());

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

				m_blocks.emplace_back(std::move(block));
			}
		}
	}
}

// ƒQ[ƒ€‚ÌI—¹ˆ—
Game::~Game()
{
	delete m_frame_timer;
	delete m_input;
	delete m_paddle;
}

// ƒQ[ƒ€‚ÌXVˆ—
void Game::Update(void)
{
	m_frame_timer->Update();
	m_input->Update();
	m_paddle->Update();
	m_ball->Update();
}

// ƒQ[ƒ€‚Ì•`‰æˆ—
void Game::Render(void)
{
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
	m_paddle->Render();

	for (auto itr = m_blocks.begin(); itr != m_blocks.end(); ++itr) {
		(*itr)->Render();
	}

	m_ball->Render();
}
