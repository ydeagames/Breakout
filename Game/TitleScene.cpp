#include "TitleScene.h"

// <ƒV[ƒ“>

std::shared_ptr<Scene> TitleScene::Create()
{
	return std::make_shared<TitleScene>();
}

TitleScene::TitleScene()
	: Scene()
{

}

TitleScene::~TitleScene()
{

}
