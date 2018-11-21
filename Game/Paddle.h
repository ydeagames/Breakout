#pragma once

class Paddle : public Component
{
private:
	InputButton m_key_left;
	InputButton m_key_right;
	InputButton m_key_turnleft;
	InputButton m_key_turnright;
public:
	Paddle(const InputButton& key_left, const InputButton& key_right, const InputButton& key_turnleft, const InputButton& key_turnright);

	void Update() override;
};

