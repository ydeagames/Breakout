#pragma once

// <�V�[��>
class PlayScene : public Scene
{
private:
	static const int STAGE_DATA[3][8];

public:
	static std::shared_ptr<Scene> Create();

public:
	PlayScene();
	virtual ~PlayScene();
};
