#include "PlayScene.h"
#include "GameMain.h"
#include "Paddle.h"
#include "Block.h"
#include "Ball.h"
// <ƒV[ƒ“>

class Score : public Component {
public:
	Timer timer;
	float score;
};

PlayScene::PlayScene()
	: Scene()
{
	{
		auto score = GameObject::Create("Score");
		score->transform()->position = { SCREEN.GetX(HorizontalSide::LEFT) + 20.f, SCREEN.GetY(VerticalSide::TOP) + 20.f };
		score->transform()->scale = { 80, 16 };
		class ScoreBehaviour : public Component
		{
			std::weak_ptr<Score> wscore;
			std::weak_ptr<TextRenderer> wtext;

			void Start()
			{
				wscore = gameObject()->GetComponent<Score>();
				wtext = gameObject()->GetComponent<TextRenderer>();
				if (auto score = wscore.lock())
				{
					score->timer.Start(30);
				}
			}

			void Update()
			{
				if (auto text = wtext.lock())
					if (auto score = wscore.lock())
						text->text = "Score: " + std::to_string(score->score) + "   Žc‚èŽžŠÔ: " + std::to_string(score->timer.GetRemaining());
			}
		};
		score->AddNewComponent<ScoreBehaviour>();
		score->AddNewComponent<TextRenderer>("");
		score->AddNewComponent<Score>();
	}

	{
		auto paddle = GameObject::Create("Paddle", 3);
		paddle->transform()->position = { SCREEN.GetX(HorizontalSide::CENTER), SCREEN.GetY(VerticalSide::BOTTOM) - 20.f };
		paddle->transform()->scale = { 80, 16 };
		paddle->AddNewComponent<Rigidbody>(Vec2{}, std::vector<int>{ {1} });
		paddle->AddNewComponent<Paddle>(SCREEN.Expand(-200));
		paddle->AddNewComponent<BoxRenderer>();
		paddle->AddNewComponentAs<Collider, BoxCollider>(Box{ Vec2{}, paddle->transform()->scale }, false);
		class PaddleCollisionEvent : public CollisionEvent
		{
			void OnCollisionEnter(GameObject& other)
			{
				if (other.tag == "Block")
					gameObject()->Destroy();
			}
		};
		paddle->AddNewComponentAs<CollisionEvent, PaddleCollisionEvent>();
	}

	{
		auto ball = GameObject::Create("Ball", 2);
		ball->transform()->position = SCREEN.GetCenter();
		ball->transform()->scale = { 5, 5 };
		ball->AddNewComponent<Rigidbody>(Vec2{ 5,5 }, std::vector<int>{ {1, 3} });
		ball->AddNewComponent<Ball>();
		ball->AddNewComponent<CircleRenderer>();
		ball->AddNewComponentAs<Collider, CircleCollider>(Circle{ Vec2{}, ball->transform()->scale.x }, false);
	}

	{
		auto ball = GameObject::Create("BlockGenerator");
		ball->transform()->position = SCREEN.GetCenter();
		ball->transform()->scale = SCREEN.GetSize();
		class BlockGenerator : public Component
		{
			Timer timer;

			void Start()
			{
				timer = Timer{}.Start(1);
			}

			void Update()
			{
				if (timer.IsFinished())
				{
					timer.ResetRemaining();

					auto block = GameObject::Create("Block", 1, "Block");
					block->transform()->scale = { 80, 20 };
					block->AddNewComponent<Block>();
					block->AddNewComponentAs<Collider, BoxCollider>(Box{ Vec2{}, block->transform()->scale }, false);
					class BlockCollisionEvent : public CollisionEvent
					{
						void OnCollisionEnter(GameObject& other)
						{
							gameObject()->Destroy();
							GameObject::Find("Score")->GetComponent<Score>()->score++;
						}
					};
					block->AddNewComponentAs<CollisionEvent, BlockCollisionEvent>();
					class BlockBehaviour : public Component
					{
						std::weak_ptr<Rigidbody> rigidbody;

						void Start()
						{
							rigidbody = gameObject()->GetComponent<Rigidbody>();
						}

						void Update()
						{
							gameObject()->transform()->rotation = (gameObject()->transform()->position - SCREEN.GetCenter()).Angle() + DX_PI_F / 2;
							Vec2 distance = gameObject()->transform()->position - SCREEN.GetCenter();
							if (auto rigid = rigidbody.lock())
								rigid->vel = -distance.Normalized();
							if (distance.LengthSquared() < 5 * 5)
								gameObject()->Destroy();
						}
					};
					block->AddNewComponent<BlockBehaviour>();
					block->AddNewComponent<Rigidbody>();
					block->transform()->position = gameObject()->transform()->position + (Vec2::right * (gameObject()->transform()->scale / 2).Length()).Rotate(MathUtils::GetRand(DX_TWO_PI_F));
					auto renderer = std::make_shared<BoxRenderer>();
					renderer->material = Material{}.SetBase(MathUtils::GetColorHSV(MathUtils::GetRandRange(0.f, 360.f), 1, 1), .7f).SetBorder(Colors::White, 1.f, 1.f);
					block->AddComponent(renderer);

				}
			}
		};
		ball->AddNewComponent<BlockGenerator>();
	}
}

PlayScene::~PlayScene()
{

}

