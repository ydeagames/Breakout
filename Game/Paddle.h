#pragma once

class Paddle : public Component
{
private:
	InputButton m_key_left;
	InputButton m_key_right;
public:
	Paddle(const InputButton& key_left, const InputButton& key_right);

	void Update() override;
};

