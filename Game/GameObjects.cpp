#include "GameObjects.h"
#include "GameMain.h"
#include "GameUtils.h"
#include <math.h>

// �萔�̒�` ==============================================================

// �֐��̒�` ==============================================================

// <�e�I�u�W�F�N�g>
GameObject GameObject_Ball_Create(const Vec2* pos, const Vec2* vec)
{
	GameObject obj = GameObject_Create(*pos, *vec, { 5, 5 });
	obj.type = TYPE_PARTICLE_BALL;
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[1], {}, { 26, 26 }));
	obj.sprite.num_columns = 9;
	GameSprite_SetFrame(&obj.sprite, 11);
	return obj;
}

// <�S�[���I�u�W�F�N�g>
static GameObject GameObject_Planets_Goal_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_Create(*base, {}, { 20, 20 });
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[2], {}, { 34, 34 }));
	obj.sprite.num_columns = 6;
	GameSprite_SetFrame(&obj.sprite, 17);
	obj.type = TYPE_GOAL;
	obj.shape = SHAPE_CIRCLE;
	obj.sprite.color = COLOR_RED;
	GameObject_SetSize(&obj, 2, 32);
	return obj;
}

// <�S�[���I�u�W�F�N�g>
static void GameObject_Planets_Goal_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = obj->pos;
	*next = {};
}

// <�X�^�[�g�I�u�W�F�N�g>
GameObject GameObject_Planets_Start_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_Create(*base, Vec2_Sub(next, base), { 10, 10 });
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[0], {}, { 26, 26 }));
	obj.sprite.num_columns = 8;
	GameSprite_SetFrame(&obj.sprite, 12);
	obj.type = TYPE_START;
	GameObject_SetSize(&obj, 3, 25);
	GameTimer_SetRemaining(&obj.count, .5f);
	GameTimer_Resume(&obj.count);
	return obj;
}

// <�X�^�[�g�I�u�W�F�N�g>
static void GameObject_Planets_Start_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = obj->pos;
	*next = Vec2_Add(&obj->pos, &obj->vel);
}

// <�f���I�u�W�F�N�g>
static GameObject GameObject_Planets_Planet_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_Create(*base, {}, { 10, 10 });
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[0], {}, { 26, 26 }));
	obj.sprite.texture.center.x -= 0;
	obj.sprite.texture.center.y += 1.5f;
	obj.sprite.num_columns = 8;
	GameSprite_SetFrame(&obj.sprite, GetRand(7));
	obj.type = TYPE_PLANET;
	obj.shape = SHAPE_CIRCLE;
	obj.state = 0;
	obj.sprite.color = COLOR_GRAY;
	GameObject_SetSize(&obj, 3, 4);
	return obj;
}

// <�f���I�u�W�F�N�g>
static void GameObject_Planets_Planet_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = obj->pos;
	*next = {};
}

// <�r�[���I�u�W�F�N�g>
static GameObject GameObject_Planets_Beam_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_CreateLine(*base, *next);
	obj.type = TYPE_BEAM;
	obj.sprite.color = 0xE88025;
	obj.edge = 5;
	return obj;
}

// <�r�[���I�u�W�F�N�g>
static void GameObject_Planets_Beam_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = { GameObject_GetRawX(obj, LEFT), GameObject_GetRawY(obj, TOP });
	*next = { GameObject_GetRawX(obj, RIGHT), GameObject_GetRawY(obj, BOTTOM });
}

// <���[�v�I�u�W�F�N�g>
static GameObject GameObject_Planets_Warp_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_Create(*base, Vec2_Sub(next, base), { 10, 10 });
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[4], {}, { 202 / 4, 54 / 2 }));
	obj.sprite.num_columns = 4;
	GameSprite_SetFrame(&obj.sprite, 6);
	obj.type = TYPE_WARP;
	GameObject_SetSize(&obj, 2, 30);
	obj.shape = SHAPE_CIRCLE;
	return obj;
}

// <�����`���[�I�u�W�F�N�g>
static void GameObject_Planets_Warp_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = obj->pos;
	*next = Vec2_Add(&obj->pos, &obj->vel);
}

// <�����`���[�I�u�W�F�N�g>
static GameObject GameObject_Planets_Launcher_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_Create(*base, Vec2_Sub(next, base), { 10, 10 });
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[3], {}, { 20, 20 }));
	obj.sprite.num_columns = 6;
	GameSprite_SetFrame(&obj.sprite, 0);
	obj.type = TYPE_VEL;
	GameObject_SetSize(&obj, 4, 15);
	obj.shape = SHAPE_CIRCLE;
	return obj;
}

// <�����`���[�I�u�W�F�N�g>
static void GameObject_Planets_Launcher_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = obj->pos;
	*next = Vec2_Add(&obj->pos, &obj->vel);
}

// <�r�[���o�E���h�I�u�W�F�N�g>
static GameObject GameObject_Planets_BeamBounce_Create(const Vec2* base, const Vec2* next)
{
	GameObject obj = GameObject_CreateLine(*base, *next);
	obj.type = TYPE_BEAM_BOUNCE;
	obj.sprite.color = 0x55F475;
	obj.edge = 2.5f;
	return obj;
}

// <�r�[���o�E���h�I�u�W�F�N�g>
static void GameObject_Planets_BeamBounce_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	*base = { GameObject_GetRawX(obj, LEFT), GameObject_GetRawY(obj, TOP });
	*next = { GameObject_GetRawX(obj, RIGHT), GameObject_GetRawY(obj, BOTTOM });
}

// <�I�u�W�F�N�g>
GameObject GameObject_Planets_Create(int type, const Vec2* base, const Vec2* next)
{
	switch (type)
	{
	default:
	case TYPE_PLANET:
		return GameObject_Planets_Planet_Create(base, next);
	case TYPE_START:
		return GameObject_Planets_Start_Create(base, next);
	case TYPE_GOAL:
		return GameObject_Planets_Goal_Create(base, next);
	case TYPE_BEAM:
		return GameObject_Planets_Beam_Create(base, next);
	case TYPE_WARP:
		return GameObject_Planets_Warp_Create(base, next);
	case TYPE_VEL:
		return GameObject_Planets_Launcher_Create(base, next);
	case TYPE_BEAM_BOUNCE:
		return GameObject_Planets_BeamBounce_Create(base, next);
	}
}

// <�I�u�W�F�N�g>
void GameObject_Planets_Serialize(const GameObject* obj, Vec2* base, Vec2* next)
{
	switch (obj->type)
	{
	default:
	case TYPE_PLANET:
		GameObject_Planets_Planet_Serialize(obj, base, next);
		break;
	case TYPE_START:
		GameObject_Planets_Start_Serialize(obj, base, next);
		break;
	case TYPE_GOAL:
		GameObject_Planets_Goal_Serialize(obj, base, next);
		break;
	case TYPE_BEAM:
		GameObject_Planets_Beam_Serialize(obj, base, next);
		break;
	case TYPE_WARP:
		GameObject_Planets_Warp_Serialize(obj, base, next);
		break;
	case TYPE_VEL:
		GameObject_Planets_Launcher_Serialize(obj, base, next);
		break;
	case TYPE_BEAM_BOUNCE:
		GameObject_Planets_BeamBounce_Serialize(obj, base, next);
		break;
	}
}

// <�����p�[�e�B�N��>
static GameObject GameObject_Particles_Doom_Create(const Vec2* base, const Vec2* vec)
{
	GameObject obj = GameObject_Create(*base, {}, { 20, 20 });
	obj.shape = SHAPE_CIRCLE;
	obj.sprite.color = COLOR_RED;
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[0], {}, { 26, 26 }));
	obj.sprite.num_columns = 8;
	obj.sprite.animation = GameSpriteAnimation_Create(19, 22, 8);
	obj.sprite.animation.loop_flag = FALSE;
	GameObject_SetSize(&obj, 2, 32);
	obj.type = TYPE_PARTICLE_DOOM;
	return obj;
}

// <�S�[�������p�[�e�B�N��>
static GameObject GameObject_Particles_GoalDoomSpawner_Create(const Vec2* base, const Vec2* vec)
{
	GameObject obj = GameObject_Create(*base, {}, { 50, 50 });
	obj.type = TYPE_PARTICLE_GOAL_DOOM_SPAWNER;
	GameTimer_SetRemaining(&obj.count, .75f);
	GameTimer_Resume(&obj.count);
	return obj;
}

// <�����p�[�e�B�N��>
static GameObject GameObject_Particles_GoalDoom_Create(const Vec2* base, const Vec2* vec)
{
	GameObject obj = GameObject_Create(*base, {}, { 20, 20 });
	obj.shape = SHAPE_CIRCLE;
	obj.sprite.color = COLOR_RED;
	obj.sprite = GameSprite_Create(GameTexture_Create(g_resources.texture[7], {}, { 35, 35 }));
	obj.sprite.num_columns = 7;
	obj.sprite.animation = GameSpriteAnimation_Create(7, 10, 8);
	obj.sprite.animation.loop_flag = FALSE;
	GameObject_SetSize(&obj, 2, 32);
	obj.type = TYPE_PARTICLE_GOAL_DOOM;
	return obj;
}

// <�d�̓p�[�e�B�N��>
static GameObject GameObject_Particles_Gravity_Create(const Vec2* base, const Vec2* vec)
{
	GameObject obj = GameObject_Create(*base, {}, { 2, 2 });
	obj.type = TYPE_PARTICLE_GRAVITY;
	obj.fill = TRUE;
	obj.sprite.color = COLOR_YELLOW;
	GameTimer_SetRemaining(&obj.count, GetRandF(4));
	GameTimer_Resume(&obj.count);
	return obj;
}

// <�L���p�[�e�B�N��>
static GameObject GameObject_Particles_Active_Create(const Vec2* base, const Vec2* vec)
{
	GameObject obj = GameObject_Create(*base, {}, { 2, 2 });
	obj.type = TYPE_PARTICLE_ACTIVE;
	obj.fill = TRUE;
	obj.sprite.color = COLOR_GREEN;
	return obj;
}

// <�p�[�e�B�N��>
GameObject GameObject_Particles_Create(int type, const Vec2* base, const Vec2* vec)
{
	switch (type)
	{
	default:
	case TYPE_PARTICLE_BALL:
		return GameObject_Ball_Create(base, vec);
	case TYPE_PARTICLE_DOOM:
		return GameObject_Particles_Doom_Create(base, vec);
	case TYPE_PARTICLE_GOAL_DOOM:
		return GameObject_Particles_GoalDoom_Create(base, vec);
	case TYPE_PARTICLE_GOAL_DOOM_SPAWNER:
		return GameObject_Particles_GoalDoomSpawner_Create(base, vec);
	case TYPE_PARTICLE_GRAVITY:
		return GameObject_Particles_Gravity_Create(base, vec);
	case TYPE_PARTICLE_ACTIVE:
		return GameObject_Particles_Active_Create(base, vec);
	}
}

// <�I�u�W�F�N�g���[�v�`��>
void GameObject_RenderLoop(const GameObject* obj, const GameObject* tile_area, GameObject* tile_obj, const Vec2* translate)
{
	float box_xc = GameObject_GetX(obj, CENTER_X) + translate->x;
	float box_ym = GameObject_GetY(obj, CENTER_Y) + translate->y;
	Vec2 box_t = { box_xc, box_ym };
	float go_left = GameObject_GetX(obj, LEFT);
	float go_right = GameObject_GetX(obj, RIGHT);
	float go_top = GameObject_GetY(obj, TOP);
	float go_bottom = GameObject_GetY(obj, BOTTOM);

	float sp_left = GameObject_GetX(tile_area, LEFT);
	float sp_right = GameObject_GetX(tile_area, RIGHT);
	float sp_top = GameObject_GetY(tile_area, TOP);
	float sp_bottom = GameObject_GetY(tile_area, BOTTOM);

	Vec2 sp_pos = Vec2_Add(&box_t, &obj->sprite.offset);
	Vec2 sp_size = Vec2_Scale(&obj->sprite.texture.size, obj->sprite.scale);
	float offset_x = GetLoopRangeF(go_left, sp_left, sp_right) - sp_left;
	float offset_y = GetLoopRangeF(go_top, sp_top, sp_bottom) - sp_top;

	if (sp_size.x >= 1.f && sp_size.y >= 1.f)
	{
		for (float iy = go_top + sp_size.y / 2 - offset_y/* - center_offset.y*/; iy < go_bottom; iy += sp_size.y)
		{
			for (float ix = go_left + sp_size.x / 2 - offset_x/* - center_offset.x*/; ix < go_right; ix += sp_size.x)
			{
				GameObject_Render(tile_obj, translate);
			}
		}
	}
}

// <�t�B�[���h�`��>
void GameObject_Field_Render(const GameObject* field, const Vec2* translate, int fadeout)
{
	GameObject_Render(field, translate);
	screen_start(field->sprite.texture.texture)
	{
		GameObject fieldback = *field;
		fieldback.sprite = GameSprite_CreateNone();
		fieldback.sprite.color = COLOR_BLACK;
		fieldback.fill = TRUE;
		fieldback.pos = Vec2_Scale(&fieldback.size, .5f);
		SetDrawBlendMode(DX_BLENDMODE_SUB, fadeout);
		GameObject_Render(&fieldback);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	} screen_end;
}

// <���b�Z�[�W�`��>
void GameObject_Msg_Render(const Vec2* pos, const Vec2* translate, const char* msg)
{
	int margin = 12;
	int triangle = 20;
	Vec2 size = { (float)(GetDrawStringWidthToHandle(msg, strlen(msg), g_resources.font_main) + margin * 2), (float)(FONT_SIZE_MAIN + margin * 2) };
	GameObject obj = GameObject_Create({ pos->x + size.x / 2, pos->y - size.y / 2 - triangle + 1 }, {}, size);
	obj.fill = TRUE;
	GameObject_Render(&obj, translate);
	DrawTriangleAA(pos->x + translate->x, pos->y + translate->y,
		pos->x + translate->x, pos->y - triangle + translate->y,
		pos->x + triangle + translate->x, pos->y - triangle + translate->y,
		obj.sprite.color, TRUE);
	DrawStringFToHandle(GameObject_GetX(&obj, LEFT, (float)-margin) + translate->x, GameObject_GetY(&obj, TOP, (float)-margin) + translate->y, msg, COLOR_BLACK, g_resources.font_main);
}