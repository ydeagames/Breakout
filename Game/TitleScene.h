#pragma once
#include "Scene.h"

// <�V�[��>
class TitleScene : public Scene
{
public:
	static Scene* Create();

public:
	TitleScene();
	virtual ~TitleScene();

public:
	void Update() override;
	void Render() override;
};
