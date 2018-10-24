// @file   GameMain.h
//
// @brief  ゲーム関連のヘッダファイル
//
// @date   日付
//
// @author 制作者名

#pragma once

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

// <ゲーム>
class Game
{
private:
	const float SPEED = 8;

	FrameTimer* m_frame_timer;
	JoypadInput* m_joypad;
	Vec2 m_pos;
	Vec2 m_vel;

	// メンバ関数の宣言
public:
	Game();
	~Game();

	void Update(void);
	void Render(void);
};
