// @file   GameMain.h
//
// @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//
// @date   ���t
//
// @author ����Җ�

#pragma once
#include <vector>

// <�V�X�e��>

// �Q�[���^�C�g��
const char* const GAME_TITLE = "Sample Game";

// <���>

// ��ʂ̕�[pixel]
const int SCREEN_WIDTH = 640;
// ��ʂ̍���[pixel]
const int SCREEN_HEIGHT = 480;

// ��ʂ̏�[
const int SCREEN_TOP = 0;
// ��ʂ̉��[
const int SCREEN_BOTTOM = SCREEN_HEIGHT;
// ��ʂ̍��[
const int SCREEN_LEFT = 0;
// ��ʂ̉E�[
const int SCREEN_RIGHT = SCREEN_WIDTH;

// ��ʂ̒���(X���W)
const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
// ��ʂ̒���(Y���W)
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

// <�g�p�N���X�錾>
class Paddle;
class Block;
class Ball;

// <�Q�[��>
class Game
{
private:
	static const int STAGE_DATA[3][8];

private:
	FrameTimer* m_frame_timer;
	InputManager* m_input;
	GameObject* m_paddle;
	std::vector<std::unique_ptr<GameObject>> m_blocks;
	GameObject* m_ball;

public:
	Game();
	~Game();

	void Update(void);
	void Render(void);
};
