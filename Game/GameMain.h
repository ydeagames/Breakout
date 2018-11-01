// @file   GameMain.h
//
// @brief  ゲーム関連のヘッダファイル
//
// @date   日付
//
// @author 制作者名

#pragma once
#include <vector>

// <システム>

// ゲームタイトル
const char* const GAME_TITLE = "Sample Game";

// <画面>

// 画面の幅[pixel]
const int SCREEN_WIDTH = 640;
// 画面の高さ[pixel]
const int SCREEN_HEIGHT = 480;

// 画面の上端
const int SCREEN_TOP = 0;
// 画面の下端
const int SCREEN_BOTTOM = SCREEN_HEIGHT;
// 画面の左端
const int SCREEN_LEFT = 0;
// 画面の右端
const int SCREEN_RIGHT = SCREEN_WIDTH;

// 画面の中央(X座標)
const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
// 画面の中央(Y座標)
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

// <使用クラス宣言>
class Paddle;
class Block;

// <ゲーム>
class Game
{
private:
	static const int STAGE_DATA[3][8];

private:
	FrameTimer* m_frame_timer;
	InputManager* m_input;
	Paddle* m_paddle;
	std::vector<Block> m_blocks;

public:
	Game();
	~Game();

	void Update(void);
	void Render(void);
};
