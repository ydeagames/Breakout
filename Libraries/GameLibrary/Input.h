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

	// ����
	void Consume();

	// ������Ă��邩
	bool GetButton();

	// �����ꂽ��
	bool GetButtonDown();

	// �����ꂽ��
	bool GetButtonUp();
};

// <���̓f�o�C�X>
class Input
{
public:
	virtual ~Input() {};

	// �X�V
	virtual void Update() = 0;

	// ����
	virtual void Consume(int button) = 0;

	// �{�^���n���h��
	InputButton GetInputButton(int button);

	// ������Ă��邩
	virtual bool GetButton(int button) = 0;

	// �����ꂽ��
	virtual bool GetButtonDown(int button) = 0;

	// �����ꂽ��
	virtual bool GetButtonUp(int button) = 0;
};

// <�{�^�����̓f�o�C�X>
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

// <�W���C�p�b�h���̓f�o�C�X>
class JoypadInput final : public ButtonInput
{
private:
	// �W���C�p�b�h�̎��ʎq
	int pad_id;

public:
	JoypadInput(int pad_id = DX_INPUT_KEY_PAD1);

	~JoypadInput();

	void Update() override;
};

// <�}�E�X���̓f�o�C�X>
class MouseInput final : public ButtonInput
{
private:
	Vec2 position;

public:
	MouseInput();

	~MouseInput();

	void Update() override;

	// �}�E�X�����W���擾
	const Vec2& GetPosition();

	// �}�E�X�����W��ݒ�
	void SetPosition(const Vec2& pos);
};

// <�L�[���̓f�o�C�X>
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

// <���̓f�o�C�X�}�l�[�W��>
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
