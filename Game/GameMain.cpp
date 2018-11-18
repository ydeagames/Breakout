#include "GameMain.h"
#include <cmath>
#include "Demo\DemoSceneLogo.h"
#include "Demo\DemoSceneTitle.h"
#include "Demo\DemoScenePlay.h"

// <Game�N���X>

// �Q�[���̏���������
Game::Game() :
	m_frame_timer(new FrameTimer)
{
	SceneManager& scene_manager = SceneManager::GetInstance();

	scene_manager.AddScene<DemoSceneLogo>(SceneID::LOGO);
	scene_manager.AddScene<DemoSceneTitle>(SceneID::TITLE);
	scene_manager.AddScene<DemoScenePlay>(SceneID::PLAY);

	scene_manager.SetStartScene(SceneID::TITLE);
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

	InputManager::GetInstance().Update();

	SceneManager::GetInstance().UpdateActiveScene();
}

// �Q�[���̕`�揈��
void Game::Render(void)
{
	DrawFormatString(10, 10, Colors::White, "FPS = %f", m_frame_timer->GetFrameRate());

	SceneManager::GetInstance().RenderActiveScene();
}
