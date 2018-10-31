#include "GameObject.h"
#include "GameMain.h"

#ifndef COMPLETE

using namespace MathUtils;

bool DEBUG_HITBOX = FALSE;

// <<ティック>> --------------------------------------------------------

// <最終時刻>
static int g_lastcount = -1;
// <デルタミリ秒>
static int g_deltamilliseconds = 0;

// <<テクスチャ>> ------------------------------------------------------

// <テクスチャ作成>
GameTexture::GameTexture(HGRP texture, Vec2 anchor, Vec2 size) :
	texture(texture),
	anchor(anchor),
	size(size),
	center(Vec2{ size.x / 2, size.y / 2 })
{
}

// <テクスチャなし>
GameTexture::GameTexture() :
	GameTexture(TEXTURE_NONE, Vec2{}, Vec2{})
{
}

// <<スプライト>> ------------------------------------------------------

// <スプライト作成>
GameSprite::GameSprite(GameTexture texture, float scale, float angle) :
	color(COLOR_WHITE),
	texture(texture),
	size(texture.size),
	num_columns(1),
	frame_index(0),
	offset(Vec2{}),
	scale(scale),
	angle(angle)
{
}

// <スプライトなし>
GameSprite GameSprite_CreateNone() :
	GameSprite(GameTexture{}, 0, 0)
{
}

// <スプライト更新>
void GameSprite::SetFrame(int frame)
{
	// フレーム番号
	frame_index = frame;
}

// <スプライト描画>
void GameSprite::Render(const Vec2* pos)
{
	int column = frame_index%num_columns;
	int row = frame_index / num_columns;

	Vec2 anchor = texture.anchor + Vec2{ size.x * column, size.y * row };

	// スプライト描画
	DrawRectRotaGraph2F(
		pos->x + offset.x, pos->y + offset.y,
		(int)anchor.x, (int)anchor.y,
		(int)texture.size.x, (int)texture.size.y,
		texture.center.x, texture.center.y,
		(double)scale,
		(double)angle,
		texture.texture,
		TRUE
	);
}

// <<スプライトアニメーション>> ----------------------------------------

// <スプライトアニメーション作成>
GameSpriteAnimation(GameTexture texture, int frames_start, int frames_end, int frame_duration, float scale, float angle, bool pause) :
	GameSprite(texture, anchor, size),
	frames_start(frames_start),
	frames_end(frames_end),
	frame_duration(0),
	elapsed_time(0),
	loop_flag(true),
	pause_flag(pause),
	result(AnimationState::RUNNING)
{
}

// <スプライトアニメーションなし>
GameSpriteAnimation::GameSpriteAnimation() :
	GameSpriteAnimation(-1, -1, 1, true)
{
}

// <スプライトアニメーション更新>
AnimationState GameSpriteAnimation::Update()
{
	if (!pause_flag && frame_start >= 0 && frame_end >= 0)
	{
		// アニメーションしているか
		result = AnimationState::RUNNING;
		// 経過時間
		elapsed_time++;
		// 最初のフレーム以上
		frame_index = GetMax(frame_index, frame_start);

		// フレーム経過
		if (elapsed_time > frame_duration)
		{
			// 経過時間
			elapsed_time = 0;
			// フレーム番号
			frame_index++;

			// 最初に戻る
			if (frame_index > frame_end)
			{
				// ループするなら
				if (loop_flag)
					// 最初に戻る
					frame_index = frame_start;
				else
					// 最後のフレームで停止
					frame_index = frame_end;
				// アニメーション完了
				result = AnimationState::FINISHED;
			}
		}
	}
	else
		// アニメーションしているか
		result = ANIMATION_IDLE;

	return result;
}

// <<ティック>> --------------------------------------------------------

// <オブジェクト作成>
void GameTick_Update(void)
{
	int now = GetNowCount();
	g_deltamilliseconds = GetMin(100, now - g_lastcount);
	g_lastcount = now;
}

// <<オブジェクト>> ----------------------------------------------------

// <オブジェクト作成>
GameObject(Vec2 pos, Vec2 vel, Vec2 size) :
	pos(pos),
	vel(vel),
	size(size),
	shape(Shape::Box),
	fill(false),
	edge(0),
	sprite_connection(Connection::NONE),
	alive(true),
	state(1),
	type(0),
	count(Timer{})
{
	return{ pos, vel, size, SHAPE_BOX, GameSprite_CreateNone(), FALSE, 0, CONNECTION_NONE, TRUE, 1, 0, Timer{} };
}

// <線オブジェクト作成>
static GameObject GameObject::CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel)
{
	Vec2 pos = (pos1 + pos2) * .5f;
	Vec2 size = pos2 - pos1;
	GameObject obj = GameObject{ pos, vel, size };
	obj.shape = SHAPE_LINE;
	return obj;
}

// <オブジェクト削除>
void GameObject::Dispose(GameObject* obj)
{
	obj->alive = FALSE;
}

// <オブジェクト確認>
bool GameObject::IsAlive(const GameObject* obj)
{
	return obj->alive;
}

// <オブジェクト座標更新>
void GameObject::UpdatePosition(GameObject* obj)
{
	obj->pos.x += obj->vel.x;// *(g_deltamilliseconds / 17.f);
	obj->pos.y += obj->vel.y;// *(g_deltamilliseconds / 17.f);
}

// <オブジェクトXオフセット>
float GameObject::OffsetX(const GameObject* obj, ObjectSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case LEFT:
		offset = -(padding + GetAbs(obj->size.x) / 2.f);
		break;
	case RIGHT:
		offset = (padding + GetAbs(obj->size.x) / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトXオフセット>
float GameObject::OffsetY(const GameObject* obj, ObjectSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case TOP:
		offset = -(padding + GetAbs(obj->size.y) / 2.f);
		break;
	case BOTTOM:
		offset = (padding + GetAbs(obj->size.y) / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトX位置ゲット>
float GameObject::GetX(const GameObject* obj, ObjectSide side, float padding)
{
	return OffsetX(obj, side, obj->pos.x, padding);
}

// <オブジェクトY位置ゲット>
float GameObject::GetY(const GameObject* obj, ObjectSide side, float padding)
{
	return OffsetY(obj, side, obj->pos.y, padding);
}

// <オブジェクトXオフセット>
float GameObject::OffsetRawX(const GameObject* obj, ObjectSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case LEFT:
		offset = -(padding + obj->size.x / 2.f);
		break;
	case RIGHT:
		offset = (padding + obj->size.x / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトXオフセット>
float GameObject::OffsetRawY(const GameObject* obj, ObjectSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case TOP:
		offset = -(padding + obj->size.y / 2.f);
		break;
	case BOTTOM:
		offset = (padding + obj->size.y / 2.f);
		break;
	}
	return pos + offset;
}

// <オブジェクトX位置ゲット>
float GameObject::GetRawX(const GameObject* obj, ObjectSide side, float padding)
{
	return OffsetRawX(obj, side, obj->pos.x, padding);
}

// <オブジェクトY位置ゲット>
float GameObject::GetRawY(const GameObject* obj, ObjectSide side, float padding)
{
	return OffsetRawY(obj, side, obj->pos.y, padding);
}

// <オブジェクト描画>
void GameObject::Render(const GameObject* obj, const Vec2* translate)
{
	float box_xl = GetRawX(LEFT) + translate->x;
	float box_xc = GetRawX(CENTER_X) + translate->x;
	float box_xr = GetRawX(RIGHT) + translate->x;
	float box_yt = GetRawY(TOP) + translate->y;
	float box_ym = GetRawY(CENTER_Y) + translate->y;
	float box_yb = GetRawY(BOTTOM) + translate->y;
	Vec2 box_t = { box_xc, box_ym };

	// テクスチャを確認
	if (obj->sprite.texture.texture != TEXTURE_NONE)
	{
		if (obj->sprite.texture.texture != TEXTURE_MISSING)
		{
			switch (obj->sprite_connection)
			{
			case CONNECTION_LOOP:
			case CONNECTION_BARRIER:
			{
				// リピートタイル (回転、テクスチャ中心座標 には未対応)
				Vec2 center_offset = obj->sprite.texture.center * obj->sprite.scale;
				Vec2 sp_pos = box_t + obj->sprite.offset;
				Vec2 sp_size = obj->sprite.texture.size * obj->sprite.scale;

				float go_left = box_xl;
				float go_right = box_xr;
				float go_top = box_yt;
				float go_bottom = box_yb;

				float sp_left = sp_pos.x - sp_size.x / 2;
				float sp_right = sp_pos.x + sp_size.x / 2;
				float sp_top = sp_pos.y - sp_size.y / 2;
				float sp_bottom = sp_pos.y + sp_size.y / 2;

				switch (obj->sprite_connection)
				{
				case CONNECTION_BARRIER:
					if (sp_left < go_right && go_left < sp_right && sp_top < go_bottom && go_top < sp_bottom)
						GameSprite_Render(&obj->sprite, &box_t);
					break;
				case CONNECTION_LOOP:
					float offset_x = GetLoopRange(go_left, sp_left, sp_right) - sp_left;
					float offset_y = GetLoopRange(go_top, sp_top, sp_bottom) - sp_top;

					if (sp_size.x >= 1.f && sp_size.y >= 1.f)
					{
						for (float iy = go_top + sp_size.y / 2 - offset_y - center_offset.y; iy < go_bottom; iy += sp_size.y)
						{
							for (float ix = go_left + sp_size.x / 2 - offset_x - center_offset.x; ix < go_right; ix += sp_size.x)
							{
								GameSprite_Render(&obj->sprite, &Vec2{ ix + sp_size.x / 2 - obj->sprite.offset.x, iy + sp_size.y / 2 - obj->sprite.offset.y });

								if (DEBUG_HITBOX)
									DrawBoxAA(ix, iy, ix + sp_size.x, iy + sp_size.y, obj->sprite.color, FALSE, .5f);
							}
						}
					}

					break;
				}

				break;
			}
			default:
				GameSprite_Render(&obj->sprite, &box_t);
				break;
			}
		}
		else
		{
			// NULLテクスチャを表示
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, COLOR_BLACK, TRUE);
			DrawBoxAA(box_xl, box_yt, box_xc, box_ym, COLOR_FUCHSIA, TRUE);
			DrawBoxAA(box_xc, box_ym, box_xr, box_yb, COLOR_FUCHSIA, TRUE);
			//DrawBoxAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, FALSE, .5f);
		}
	}

	// 図形描画
	switch (obj->shape)
	{
	default:
	case SHAPE_BOX:
		// 矩形描画
		if (obj->fill)
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, TRUE);
		if (obj->edge > 0)
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, FALSE, obj->edge);
		if (DEBUG_HITBOX)
		{
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, FALSE, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, .5f);
			DrawLineAA(box_xr, box_yt, box_xl, box_yb, obj->sprite.color, .5f);
		}
		break;
	case SHAPE_CIRCLE:
	{
		float r1 = GetMin(GetAbs(obj->size.x), GetAbs(obj->size.y)) / 2;
		// 円
		if (obj->fill)
			DrawCircleAA(box_xc, box_ym, r1, 120, obj->sprite.color, TRUE);
		if (obj->edge > 0)
			DrawCircleAA(box_xc, box_ym, r1, 120, obj->sprite.color, FALSE, obj->edge);
		if (DEBUG_HITBOX)
		{
			DrawCircleAA(box_xc, box_ym, r1, 120, obj->sprite.color, FALSE, .5f);
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, FALSE, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, .5f);
			DrawLineAA(box_xr, box_yt, box_xl, box_yb, obj->sprite.color, .5f);
		}
		break;
	}
	case SHAPE_LINE:
	{
		float r1 = obj->edge;
		// 線
		if (DEBUG_HITBOX)
			obj->size.Render(Vec2{ box_xl, box_yt }, obj->sprite.color, .5f);
		DrawLineAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, r1);
		break;
	}
	}
}

// <オブジェクトサイズ変更>
void GameObject::SetSize(GameObject* obj, float scale, float size)
{
	obj->sprite.scale = scale;
	obj->size = { size * scale, size * scale };
}

// <<フィールドオブジェクト>> ------------------------------------------

// <フィールドオブジェクト作成>
GameObject GameObject::Field_Create(void)
{
	return GameObject{
		Vec2{ static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) },
		Vec2{},
		Vec2{ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) }
	};
}

// <フィールド上下衝突処理>
ObjectSide GameObject::Field_CollisionVertical(const GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge)
{
	// ヒットサイド
	ObjectSide side_hit = NONE;

	// コウラ・上下壁当たり判定
	{
		// 縁に応じてパディングを調整
		float padding_top = GetY(field, TOP);
		float padding_bottom = GetY(field, BOTTOM);
		switch (edge)
		{
		case EDGESIDE_INNER:
			padding_top = OffsetY(obj, BOTTOM, padding_top);
			padding_bottom = OffsetY(obj, TOP, padding_bottom);
			break;
		case EDGESIDE_OUTER:
			padding_top = OffsetY(obj, TOP, padding_top);
			padding_bottom = OffsetY(obj, BOTTOM, padding_bottom);
			break;
		}

		// 当たり判定
		if (obj->pos.y < padding_top)
			side_hit = TOP;
		else if (padding_bottom <= obj->pos.y)
			side_hit = BOTTOM;

		// フィールドのつながり
		switch (connection)
		{
		case CONNECTION_BARRIER:
			// 壁にあたったら調整
			obj->pos.y = GetClamp(obj->pos.y, padding_top, padding_bottom);
			break;
		case CONNECTION_LOOP:
			// 壁にあたったらループ
			obj->pos.y = GetLoopRange(obj->pos.y, padding_top, padding_bottom);
			break;
		}
	}

	return side_hit;
}

// <フィールド左右衝突処理>
ObjectSide GameObject::Field_CollisionHorizontal(const GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge)
{
	// ヒットサイド
	ObjectSide side_hit = NONE;

	// コウラ・左右壁当たり判定
	{
		// 縁に応じてパディングを調整
		float padding_left = GetX(field, LEFT);
		float padding_right = GetX(field, RIGHT);
		switch (edge)
		{
		case EDGESIDE_INNER:
			padding_left = OffsetX(obj, RIGHT, padding_left);
			padding_right = OffsetX(obj, LEFT, padding_right);
			break;
		case EDGESIDE_OUTER:
			padding_left = OffsetX(obj, LEFT, padding_left);
			padding_right = OffsetX(obj, RIGHT, padding_right);
			break;
		}

		// 当たり判定
		if (obj->pos.x < padding_left)
			side_hit = LEFT;
		else if (padding_right <= obj->pos.x)
			side_hit = RIGHT;

		// フィールドのつながり
		switch (connection)
		{
		case CONNECTION_BARRIER:
			// 壁にあたったら調整
			obj->pos.x = GetClamp(obj->pos.x, padding_left, padding_right);
			break;
		case CONNECTION_LOOP:
			// 壁にあたったらループ
			obj->pos.x = GetLoopRange(obj->pos.x, padding_left, padding_right);
			break;
		}
	}

	return side_hit;
}

#endif COMPLETE
