#pragma once

// <デバッグ用当たり判定表示>
extern bool DEBUG_HITBOX;

// <横位置関係>
enum class HorizontalSide
{
	NONE,
	CENTER,						// X中央
	LEFT,						// 左
	RIGHT,						// 右
};

// <縦位置関係>
enum class VerticalSide
{
	NONE,
	CENTER,						// Y中央
	TOP,						// 上
	BOTTOM,						// 下
};

// <縁の位置> 
enum class Edge
{
	CENTER,						// 縁の上
	OUTER,						// 縁の外側
	INNER,						// 縁の内側
};

// <ワールドのつながり>
enum class Connection
{
	NONE,						// 繋がりなし、見えない空間に移動
	BARRIER,					// 壁があり、進めない
	LOOP,						// 反対側から出てくる
};

// <オブジェクトの形>
enum class Shape
{
	BOX,						// 長方形
	CIRCLE,						// 円
	LINE,						// 線
};

// <アニメーションの結果>
enum class AnimationState
{
	RUNNING,					// アニメーションが実行中の状態
	FINISHED,					// アニメーション再生が完了した状態
	IDLE,						// アニメーションしていない状態
};

// <テクスチャ>
class GameTexture
{
public:
	HGRP texture;				// <テクスチャ>
	Vec2 anchor;				// <テクスチャ基点>
	Vec2 size;					// <テクスチャサイズ>
	Vec2 center;				// <テクスチャ中心>
public:
	static constexpr int TEXTURE_MISSING = -1;		// テクスチャが見つかりません
	static constexpr int TEXTURE_NONE = -2;			// テクスチャなし

	// <テクスチャ作成>
	GameTexture(HGRP texture, Vec2 anchor, Vec2 size);

	// <テクスチャなし>
	GameTexture();
};

// <スプライトオブジェクト>
class GameSprite
{
public:
	unsigned int color;			// <色>
	GameTexture texture;		// <テクスチャ>
	Vec2 size;					// <サイズ>
	int num_columns;			// <1行あたりのフレーム数>
	int frame_index;			// <現在のフレームのインデックス>
	Vec2 offset;				// <オフセット>
	float scale;				// <スケール>
	float angle;				// <回転>
public:
	GameSprite(GameTexture texture, float scale = 1, float angle = 0);

	// <スプライトなし>
	GameSprite();

	virtual ~GameSprite() {};

	// <スプライト更新>
	void SetFrame(int frame);

	// <スプライト描画>
	void Render(const Vec2* pos);
};

// <スプライトアニメーション>
class GameSpriteAnimation : public GameSprite
{
public:
	int frame_start;			// 開始フレームのインデックス
	int frame_end;				// 終了フレームのインデックス
	int frame_duration;			// フレーム間隔
	int elapsed_time;			// 現在のフレームの経過時間
	bool loop_flag;				// アニメーションのループ
	bool pause_flag;			// アニメーションの停止
	AnimationState result;		// 最後の状態
public:
	// <スプライトアニメーション作成>
	GameSpriteAnimation(GameTexture texture, int frames_start, int frames_end, int frame_duration, float scale = 1, float angle = 0, bool pause = false);

	// <スプライトアニメーションなし>
	GameSpriteAnimation();

	virtual ~GameSpriteAnimation() {};

	// <スプライトアニメーション更新>
	AnimationState Update();
};

// <ゲームオブジェクト>
class GameObject
{
public:
	Vec2 pos;					// <位置>
	Vec2 vel;					// <速度>
	Vec2 size;					// <大きさ>
	Shape shape;				// <形>
	GameSprite sprite;			// <スプライト>
	bool fill;					// <塗りつぶし>
	float edge;					// <縁>
	Connection sprite_connection;	// <スプライトのつながり>
	bool alive;					// <表示状態>
	int state;					// <状態>
	int type;					// <タイプ>
	Timer count;			// <カウンタ>
public:
	// <オブジェクト作成>
	GameObject(Vec2 pos = {}, Vec2 vel = {}, Vec2 size = {});

	virtual ~GameObject() {};

	// <線オブジェクト作成>
	static GameObject CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel = {});

	// <オブジェクト削除>
	void Dispose();

	// <オブジェクト確認>
	bool IsAlive();

	// <オブジェクト座標更新>
	void UpdatePosition();

	// <オブジェクトXオフセット>
	float OffsetX(HorizontalSide side, float pos = 0.f, float margin = 0.f);

	// <オブジェクトXオフセット>
	float OffsetY(VerticalSide side, float pos = 0.f, float margin = 0.f);

	// <オブジェクトX位置ゲット>
	float GetX(HorizontalSide side, float margin = 0.f);

	// <オブジェクトY位置ゲット>
	float GetY(VerticalSide side, float margin = 0.f);

	// <オブジェクトXオフセット>
	float OffsetRawX(HorizontalSide side, float pos, float padding = 0.f);

	// <オブジェクトXオフセット>
	float OffsetRawY(VerticalSide side, float pos, float padding = 0.f);

	// <オブジェクトX位置ゲット>
	float GetRawX(HorizontalSide side, float padding = 0.f);

	// <オブジェクトY位置ゲット>
	float GetRawY(VerticalSide side, float padding = 0.f);

	// <オブジェクト描画>
	void Render(Vec2* translate = &Vec2{});

	// <弾オブジェクトサイズ変更>
	void SetSize(float scale, float size = 10);
};

class Field : GameObject
{
public:
	// <フィールドオブジェクト作成>
	Field(void);

	virtual ~Field() {};

	// <フィールド上下衝突処理>
	VerticalSide CollisionVertical(GameObject* obj, Connection connection, Edge edge);

	// <フィールド左右衝突処理>
	HorizontalSide CollisionHorizontal(GameObject* obj, Connection connection, Edge edge);
};

// <オブジェクト作成>
void GameTick_Update(void);

