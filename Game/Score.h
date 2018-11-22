#pragma once


class Score final : public Singleton<Score>
{
private:
	Score() = default;
	friend class Singleton<Score>;

public:
	bool alive;
	Timer timer;
	float score;
};