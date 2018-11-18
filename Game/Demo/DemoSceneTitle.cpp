#include "DemoSceneTitle.h"

DemoSceneTitle::DemoSceneTitle()
	: Scene()
{
	// イベントオブジェクト
	auto evnt = GameObject::Create("Event");
	// TODO 継承型も親の方でGetComponentできるように
	class TimerScript : public Component
	{
	private:
		Timer timer;

	public:
		void Start()
		{
			timer = Timer{}.SetRemaining(2).Resume();
		}

		void Update()
		{
			if (timer.IsFinished())
				SceneManager::GetInstance().RequestScene(SceneID::LOGO);
		}
	};
	evnt->AddNewComponent<TimerScript>();

	auto label = GameObject::Create("Label");
	label->transform()->position.y += 50;
	label->AddNewComponent<TextRenderer>("タイトルシーン (2秒経過→Logo)");
}

DemoSceneTitle::~DemoSceneTitle()
{
}
