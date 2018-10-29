#include "GameObject.h"
#include "GameMain.h"

#ifdef COMPLETE

using namespace MathUtils;

bool DEBUG_HITBOX = FALSE;

// <<�e�B�b�N>> --------------------------------------------------------

// <�ŏI����>
static int g_lastcount = -1;
// <�f���^�~���b>
static int g_deltamilliseconds = 0;

// <<�e�N�X�`��>> ------------------------------------------------------

// <�e�N�X�`���쐬>
GameTexture::GameTexture(HGRP texture, Vec2 anchor, Vec2 size) :
	texture(texture),
	anchor(anchor),
	size(size),
	center(Vec2{ size.x / 2, size.y / 2 })
{
}

// <�e�N�X�`���Ȃ�>
GameTexture::GameTexture() :
	GameTexture(TEXTURE_NONE, Vec2{}, Vec2{})
{
}

// <<�X�v���C�g>> ------------------------------------------------------

// <�X�v���C�g�쐬>
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

// <�X�v���C�g�Ȃ�>
GameSprite GameSprite_CreateNone() :
	GameSprite(GameTexture{}, 0, 0)
{
}

// <�X�v���C�g�X�V>
void GameSprite::SetFrame(int frame)
{
	// �t���[���ԍ�
	frame_index = frame;
}

// <�X�v���C�g�`��>
void GameSprite::Render(const Vec2* pos)
{
	int column = frame_index%num_columns;
	int row = frame_index / num_columns;

	Vec2 anchor = texture.anchor + Vec2{ size.x * column, size.y * row };

	// �X�v���C�g�`��
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

// <<�X�v���C�g�A�j���[�V����>> ----------------------------------------

// <�X�v���C�g�A�j���[�V�����쐬>
GameSpriteAnimation::GameSpriteAnimation(HGRP texture, int frames_start, int frames_end, int frame_duration, Vec2 anchor, Vec2 size, bool pause) :
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

// <�X�v���C�g�A�j���[�V�����Ȃ�>
GameSpriteAnimation::GameSpriteAnimation() :
	GameSpriteAnimation(-1, -1, 1, true)
{
}

// <�X�v���C�g�A�j���[�V�����X�V>
AnimationState GameSpriteAnimation::Update()
{
	if (!pause_flag && frame_start >= 0 && frame_end >= 0)
	{
		// �A�j���[�V�������Ă��邩
		result = AnimationState::RUNNING;
		// �o�ߎ���
		elapsed_time++;
		// �ŏ��̃t���[���ȏ�
		frame_index = GetMax(frame_index, frame_start);

		// �t���[���o��
		if (elapsed_time > frame_duration)
		{
			// �o�ߎ���
			elapsed_time = 0;
			// �t���[���ԍ�
			frame_index++;

			// �ŏ��ɖ߂�
			if (frame_index > frame_end)
			{
				// ���[�v����Ȃ�
				if (loop_flag)
					// �ŏ��ɖ߂�
					frame_index = frame_start;
				else
					// �Ō�̃t���[���Œ�~
					frame_index = frame_end;
				// �A�j���[�V��������
				result = ANIMATION_FINISHED;
			}
		}
	}
	else
		// �A�j���[�V�������Ă��邩
		result = ANIMATION_IDLE;

	return result;
}

// <<�e�B�b�N>> --------------------------------------------------------

// <�I�u�W�F�N�g�쐬>
void GameTick_Update(void)
{
	int now = GetNowCount();
	g_deltamilliseconds = GetMin(100, now - g_lastcount);
	g_lastcount = now;
}

// <<�I�u�W�F�N�g>> ----------------------------------------------------

// <�I�u�W�F�N�g�쐬>
GameObject GameObject_Create(Vec2 pos, Vec2 vel, Vec2 size)
{
	return{ pos, vel, size, SHAPE_BOX, GameSprite_CreateNone(), FALSE, 0, CONNECTION_NONE, TRUE, 1, 0, Timer{} };
}

// <���I�u�W�F�N�g�쐬>
GameObject GameObject_CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel)
{
	Vec2 pos = (pos1 + pos2) * .5f;
	Vec2 size = pos2 - pos1;
	GameObject obj = GameObject_Create(pos, vel, size);
	obj.shape = SHAPE_LINE;
	return obj;
}

// <�I�u�W�F�N�g�폜>
void GameObject_Dispose(GameObject* obj)
{
	obj->alive = FALSE;
}

// <�I�u�W�F�N�g�m�F>
bool GameObject_IsAlive(const GameObject* obj)
{
	return obj->alive;
}

// <�I�u�W�F�N�g���W�X�V>
void GameObject_UpdatePosition(GameObject* obj)
{
	obj->pos.x += obj->vel.x;// *(g_deltamilliseconds / 17.f);
	obj->pos.y += obj->vel.y;// *(g_deltamilliseconds / 17.f);
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetX(const GameObject* obj, ObjectSide side, float pos, float padding)
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

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetY(const GameObject* obj, ObjectSide side, float pos, float padding)
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

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetX(const GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetX(obj, side, obj->pos.x, padding);
}

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetY(const GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetY(obj, side, obj->pos.y, padding);
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetRawX(const GameObject* obj, ObjectSide side, float pos, float padding)
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

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetRawY(const GameObject* obj, ObjectSide side, float pos, float padding)
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

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetRawX(const GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetRawX(obj, side, obj->pos.x, padding);
}

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetRawY(const GameObject* obj, ObjectSide side, float padding)
{
	return GameObject_OffsetRawY(obj, side, obj->pos.y, padding);
}

// <�I�u�W�F�N�g�`��>
void GameObject_Render(const GameObject* obj, const Vec2* translate)
{
	float box_xl = GameObject_GetRawX(obj, LEFT) + translate->x;
	float box_xc = GameObject_GetRawX(obj, CENTER_X) + translate->x;
	float box_xr = GameObject_GetRawX(obj, RIGHT) + translate->x;
	float box_yt = GameObject_GetRawY(obj, TOP) + translate->y;
	float box_ym = GameObject_GetRawY(obj, CENTER_Y) + translate->y;
	float box_yb = GameObject_GetRawY(obj, BOTTOM) + translate->y;
	Vec2 box_t = { box_xc, box_ym };

	// �e�N�X�`�����m�F
	if (obj->sprite.texture.texture != TEXTURE_NONE)
	{
		if (obj->sprite.texture.texture != TEXTURE_MISSING)
		{
			switch (obj->sprite_connection)
			{
			case CONNECTION_LOOP:
			case CONNECTION_BARRIER:
			{
				// ���s�[�g�^�C�� (��]�A�e�N�X�`�����S���W �ɂ͖��Ή�)
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
			// NULL�e�N�X�`����\��
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, COLOR_BLACK, TRUE);
			DrawBoxAA(box_xl, box_yt, box_xc, box_ym, COLOR_FUCHSIA, TRUE);
			DrawBoxAA(box_xc, box_ym, box_xr, box_yb, COLOR_FUCHSIA, TRUE);
			//DrawBoxAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, FALSE, .5f);
		}
	}

	// �}�`�`��
	switch (obj->shape)
	{
	default:
	case SHAPE_BOX:
		// ��`�`��
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
		// �~
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
		// ��
		if (DEBUG_HITBOX)
			obj->size.Render(Vec2{ box_xl, box_yt }, obj->sprite.color, .5f);
		DrawLineAA(box_xl, box_yt, box_xr, box_yb, obj->sprite.color, r1);
		break;
	}
	}
}

// <�I�u�W�F�N�g�T�C�Y�ύX>
void GameObject_SetSize(GameObject* obj, float scale, float size)
{
	obj->sprite.scale = scale;
	obj->size = { size * scale, size * scale };
}

// <<�t�B�[���h�I�u�W�F�N�g>> ------------------------------------------

// <�t�B�[���h�I�u�W�F�N�g�쐬>
GameObject GameObject_Field_Create(void)
{
	return GameObject_Create(
		Vec2{ static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) },
		Vec2{},
		Vec2{ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) });
}

// <�t�B�[���h�㉺�Փˏ���>
ObjectSide GameObject_Field_CollisionVertical(const GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge)
{
	// �q�b�g�T�C�h
	ObjectSide side_hit = NONE;

	// �R�E���E�㉺�Ǔ����蔻��
	{
		// ���ɉ����ăp�f�B���O�𒲐�
		float padding_top = GameObject_GetY(field, TOP);
		float padding_bottom = GameObject_GetY(field, BOTTOM);
		switch (edge)
		{
		case EDGESIDE_INNER:
			padding_top = GameObject_OffsetY(obj, BOTTOM, padding_top);
			padding_bottom = GameObject_OffsetY(obj, TOP, padding_bottom);
			break;
		case EDGESIDE_OUTER:
			padding_top = GameObject_OffsetY(obj, TOP, padding_top);
			padding_bottom = GameObject_OffsetY(obj, BOTTOM, padding_bottom);
			break;
		}

		// �����蔻��
		if (obj->pos.y < padding_top)
			side_hit = TOP;
		else if (padding_bottom <= obj->pos.y)
			side_hit = BOTTOM;

		// �t�B�[���h�̂Ȃ���
		switch (connection)
		{
		case CONNECTION_BARRIER:
			// �ǂɂ��������璲��
			obj->pos.y = GetClamp(obj->pos.y, padding_top, padding_bottom);
			break;
		case CONNECTION_LOOP:
			// �ǂɂ��������烋�[�v
			obj->pos.y = GetLoopRange(obj->pos.y, padding_top, padding_bottom);
			break;
		}
	}

	return side_hit;
}

// <�t�B�[���h���E�Փˏ���>
ObjectSide GameObject_Field_CollisionHorizontal(const GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge)
{
	// �q�b�g�T�C�h
	ObjectSide side_hit = NONE;

	// �R�E���E���E�Ǔ����蔻��
	{
		// ���ɉ����ăp�f�B���O�𒲐�
		float padding_left = GameObject_GetX(field, LEFT);
		float padding_right = GameObject_GetX(field, RIGHT);
		switch (edge)
		{
		case EDGESIDE_INNER:
			padding_left = GameObject_OffsetX(obj, RIGHT, padding_left);
			padding_right = GameObject_OffsetX(obj, LEFT, padding_right);
			break;
		case EDGESIDE_OUTER:
			padding_left = GameObject_OffsetX(obj, LEFT, padding_left);
			padding_right = GameObject_OffsetX(obj, RIGHT, padding_right);
			break;
		}

		// �����蔻��
		if (obj->pos.x < padding_left)
			side_hit = LEFT;
		else if (padding_right <= obj->pos.x)
			side_hit = RIGHT;

		// �t�B�[���h�̂Ȃ���
		switch (connection)
		{
		case CONNECTION_BARRIER:
			// �ǂɂ��������璲��
			obj->pos.x = GetClamp(obj->pos.x, padding_left, padding_right);
			break;
		case CONNECTION_LOOP:
			// �ǂɂ��������烋�[�v
			obj->pos.x = GetLoopRange(obj->pos.x, padding_left, padding_right);
			break;
		}
	}

	return side_hit;
}

#endif COMPLETE
