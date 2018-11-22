#pragma once

class Paddle : public Component
{
private:
	Bounds limit;

public:
	Paddle(const Bounds& limit);

public:
	void Start() override;
	void Update() override;
	void Render() override;
};

