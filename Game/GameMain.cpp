#include "GameMain.h"
#include <cmath>
#include "TitleScene.h"
#include "PlayScene.h"

// <Game�N���X>

// �Q�[���̏���������
Game::Game() :
	m_frame_timer(new FrameTimer)
{
	SceneManager& scene_manager = SceneManager::GetInstance();

	scene_manager.AddScene(SceneID::SCENE_TITLE, TitleScene::Create);
	scene_manager.AddScene(SceneID::SCENE_TITLE, PlayScene::Create);

	scene_manager.SetStartScene(SceneID::SCENE_TITLE);
}

// �Q�[���̏I������
Game::~Game()
{
	delete m_frame_timer;
}

// �Q�[���̍X�V����
void Game::Update(void)
{
	m_frame_timer->Update();
}

// �Q�[���̕`�揈��
void Game::Render(void)
{
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());
}
