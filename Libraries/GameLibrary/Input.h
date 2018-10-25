#pragma once
#include "Vec2.h"
#include <string>
#include <map>
#include <memory>

using std::string;

class Input;

class InputButton final
{
private:
	Input& input;
	int button;

public:
	InputButton(Input& input, int button) :
		input(input),
		button(button)
	{
	}

	// 消費
	void Consume();

	// 押されているか
	bool GetButton();

	// 押されたか
	bool GetButtonDown();

	// 離されたか
	bool GetButtonUp();
};

// <入力デバイス>
class Input
{
public:
	virtual ~Input() {};

	// 更新
	virtual void Update() = 0;

	// 消費
	virtual void Consume(int button) = 0;

	// ボタンハンドラ
	InputButton GetInputButton(int button);

	// 押されているか
	virtual bool GetButton(int button) = 0;

	// 押されたか
	virtual bool GetButtonDown(int button) = 0;

	// 離されたか
	virtual bool GetButtonUp(int button) = 0;
};

// <ボタン入力デバイス>
class ButtonInput : public Input
{
protected:
	int input_state;
	int input_state_last;

public:
	ButtonInput();

	virtual ~ButtonInput();

	void Consume(int button) override;

	bool GetButton(int button) override;

	bool GetButtonDown(int button) override;

	bool GetButtonUp(int button) override;
};

// <ジョイパッド入力デバイス>
class JoypadInput final : public ButtonInput
{
private:
	// ジョイパッドの識別子
	int pad_id;

public:
	JoypadInput(int pad_id = DX_INPUT_KEY_PAD1);

	~JoypadInput();

	void Update() override;
};

// <マウス入力デバイス>
class MouseInput final : public ButtonInput
{
private:
	Vec2 position;

public:
	MouseInput();

	~MouseInput();

	void Update() override;

	// マウスを座標を取得
	const Vec2& GetPosition();

	// マウスを座標を設定
	void SetPosition(const Vec2& pos);
};

// <キー入力デバイス>
class KeyInput final : public Input
{
private:
	char input_state[256];
	char input_state_last[256];

public:
	KeyInput();

	virtual ~KeyInput();

	void Update() override;

	void Consume(int button) override;

	bool GetButton(int button) override;

	bool GetButtonDown(int button) override;

	bool GetButtonUp(int button) override;
};

// <入力デバイスマネージャ>
class InputManager final
{
//private:
//	std::map<string, std::unique_ptr<Input>> inputs;

public:
	JoypadInput joypad;
	MouseInput mouse;
	KeyInput key;

	InputManager();

	void Update();
};
