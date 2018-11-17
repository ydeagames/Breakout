#pragma once
#include "Scene.h"

// <ƒV[ƒ“>
class PlayScene : public Scene
{
private:
	static const int STAGE_DATA[3][8];

public:
	static Scene* Create();

public:
	PlayScene();
	virtual ~PlayScene();
};
