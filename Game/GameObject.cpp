#include "GameObject.h"
#include "GameMain.h"

using namespace MathUtils;

bool GameObject::DEBUG_HITBOX = FALSE;

// <<�e�B�b�N>> --------------------------------------------------------

// <�ŏI����>
static int g_lastcount = -1;
// <�f���^�~���b>
static int g_deltamilliseconds = 0;

// <<�e�N�X�`��>> ------------------------------------------------------

// <�e�N�X�`���쐬>
GameTexture::GameTexture(HGRP texture, const Vec2& anchor, const Vec2& size, const Vec2& center) :
	texture(texture),
	anchor(anchor),
	size(size),
	center(center)
{
}

// <�e�N�X�`���쐬>
GameTexture::GameTexture(HGRP texture, const Vec2& anchor, const Vec2& size) :
	GameTexture(texture, anchor, size, Vec2{ size.x / 2, size.y / 2 })
{
}

// <�e�N�X�`���쐬>
GameTexture::GameTexture(HGRP texture) :
	texture(texture)
{
	anchor = {};
	size = {};
	center = {};

	if (texture == TEXTURE_MISSING)
		return;

	float width, height;
	if (GetGraphSizeF(texture, &width, &height) != -1)
	{
		size = { width, height };
		center = { width / 2, height / 2 };
		return;
	}

	texture = TEXTURE_MISSING;
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
GameSprite::GameSprite() :
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
GameSpriteAnimation::GameSpriteAnimation(GameTexture texture, int frame_start, int frame_end, int frame_duration, float scale, float angle, bool pause) :
	GameSprite(texture, scale, angle),
	frame_start(frame_start),
	frame_end(frame_end),
	frame_duration(0),
	elapsed_time(0),
	loop_flag(true),
	pause_flag(pause),
	result(AnimationState::RUNNING)
{
}

// <�X�v���C�g�A�j���[�V�����Ȃ�>
GameSpriteAnimation::GameSpriteAnimation() :
	GameSpriteAnimation(GameTexture{}, -1, -1, 1, 0, 0, true)
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
				result = AnimationState::FINISHED;
			}
		}
	}
	else
		// �A�j���[�V�������Ă��邩
		result = AnimationState::IDLE;

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
GameObject::GameObject(Vec2 pos, Vec2 vel, Vec2 size) :
	pos(pos),
	vel(vel),
	size(size),
	shape(Shape::BOX),
	fill(false),
	edge(0),
	sprite_connection(Connection::NONE),
	alive(true),
	state(1),
	type(0),
	count(Timer{})
{
}

// <���I�u�W�F�N�g�쐬>
GameObject GameObject::CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel)
{
	Vec2 pos = (pos1 + pos2) * .5f;
	Vec2 size = pos2 - pos1;
	GameObject obj = GameObject{ pos, vel, size };
	obj.shape = Shape::LINE;
	return obj;
}

// <�I�u�W�F�N�g�폜>
void GameObject::Dispose()
{
	alive = FALSE;
}

// <�I�u�W�F�N�g�m�F>
bool GameObject::IsAlive()
{
	return alive;
}

// <�I�u�W�F�N�g���W�X�V>
void GameObject::UpdatePosition()
{
	pos.x += vel.x;// *(g_deltamilliseconds / 17.f);
	pos.y += vel.y;// *(g_deltamilliseconds / 17.f);
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject::OffsetX(HorizontalSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case HorizontalSide::LEFT:
		offset = -(padding + GetAbs(size.x) / 2.f);
		break;
	case HorizontalSide::RIGHT:
		offset = (padding + GetAbs(size.x) / 2.f);
		break;
	}
	return pos + offset;
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject::OffsetY(VerticalSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case VerticalSide::TOP:
		offset = -(padding + GetAbs(size.y) / 2.f);
		break;
	case VerticalSide::BOTTOM:
		offset = (padding + GetAbs(size.y) / 2.f);
		break;
	}
	return pos + offset;
}

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject::GetX(HorizontalSide side, float padding)
{
	return OffsetX(side, pos.x, padding);
}

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject::GetY(VerticalSide side, float padding)
{
	return OffsetY(side, pos.y, padding);
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject::OffsetRawX(HorizontalSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case HorizontalSide::LEFT:
		offset = -(padding + size.x / 2.f);
		break;
	case HorizontalSide::RIGHT:
		offset = (padding + size.x / 2.f);
		break;
	}
	return pos + offset;
}

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject::OffsetRawY(VerticalSide side, float pos, float padding)
{
	float offset = 0;
	switch (side)
	{
	case VerticalSide::TOP:
		offset = -(padding + size.y / 2.f);
		break;
	case VerticalSide::BOTTOM:
		offset = (padding + size.y / 2.f);
		break;
	}
	return pos + offset;
}

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject::GetRawX(HorizontalSide side, float padding)
{
	return OffsetRawX(side, pos.x, padding);
}

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject::GetRawY(VerticalSide side, float padding)
{
	return OffsetRawY(side, pos.y, padding);
}

// <�I�u�W�F�N�g�`��>
void GameObject::Render(const Vec2* translate)
{
	float box_xl = GetRawX(HorizontalSide::LEFT) + translate->x;
	float box_xc = GetRawX(HorizontalSide::CENTER) + translate->x;
	float box_xr = GetRawX(HorizontalSide::RIGHT) + translate->x;
	float box_yt = GetRawY(VerticalSide::TOP) + translate->y;
	float box_ym = GetRawY(VerticalSide::CENTER) + translate->y;
	float box_yb = GetRawY(VerticalSide::BOTTOM) + translate->y;
	Vec2 box_t = { box_xc, box_ym };

	// �e�N�X�`�����m�F
	if (sprite.texture.texture != GameTexture::TEXTURE_NONE)
	{
		if (sprite.texture.texture != GameTexture::TEXTURE_MISSING)
		{
			switch (sprite_connection)
			{
			case Connection::LOOP:
			case Connection::BARRIER:
				{
					// ���s�[�g�^�C�� (��]�A�e�N�X�`�����S���W �ɂ͖��Ή�)
					Vec2 center_offset = sprite.texture.center * sprite.scale;
					Vec2 sp_pos = box_t + sprite.offset;
					Vec2 sp_size = sprite.texture.size * sprite.scale;

					float go_left = box_xl;
					float go_right = box_xr;
					float go_top = box_yt;
					float go_bottom = box_yb;

					float sp_left = sp_pos.x - sp_size.x / 2;
					float sp_right = sp_pos.x + sp_size.x / 2;
					float sp_top = sp_pos.y - sp_size.y / 2;
					float sp_bottom = sp_pos.y + sp_size.y / 2;

					switch (sprite_connection)
					{
					case Connection::BARRIER:
						if (sp_left < go_right && go_left < sp_right && sp_top < go_bottom && go_top < sp_bottom)
							sprite.Render(&box_t);
						break;
					case Connection::LOOP:
						float offset_x = GetLoopRange(go_left, sp_left, sp_right) - sp_left;
						float offset_y = GetLoopRange(go_top, sp_top, sp_bottom) - sp_top;

						if (sp_size.x >= 1.f && sp_size.y >= 1.f)
						{
							for (float iy = go_top + sp_size.y / 2 - offset_y - center_offset.y; iy < go_bottom; iy += sp_size.y)
							{
								for (float ix = go_left + sp_size.x / 2 - offset_x - center_offset.x; ix < go_right; ix += sp_size.x)
								{
									sprite.Render(&Vec2{ ix + sp_size.x / 2 - sprite.offset.x, iy + sp_size.y / 2 - sprite.offset.y });

									if (DEBUG_HITBOX)
										DrawBoxAA(ix, iy, ix + sp_size.x, iy + sp_size.y, sprite.color, FALSE, .5f);
								}
							}
						}

						break;
					}

					break;
				}
			default:
				sprite.Render(&box_t);
				break;
			}
		}
		else
		{
			// NULL�e�N�X�`����\��
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, COLOR_BLACK, TRUE);
			DrawBoxAA(box_xl, box_yt, box_xc, box_ym, COLOR_FUCHSIA, TRUE);
			DrawBoxAA(box_xc, box_ym, box_xr, box_yb, COLOR_FUCHSIA, TRUE);
			//DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
		}
	}

	// �}�`�`��
	switch (shape)
	{
	default:
	case Shape::BOX:
		// ��`�`��
		if (fill)
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, TRUE);
		if (edge > 0)
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, edge);
		if (DEBUG_HITBOX)
		{
			DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, .5f);
			DrawLineAA(box_xr, box_yt, box_xl, box_yb, sprite.color, .5f);
		}
		break;
	case Shape::CIRCLE:
		{
			float r1 = GetMin(GetAbs(size.x), GetAbs(size.y)) / 2;
			// �~
			if (fill)
				DrawCircleAA(box_xc, box_ym, r1, 120, sprite.color, TRUE);
			if (edge > 0)
				DrawCircleAA(box_xc, box_ym, r1, 120, sprite.color, FALSE, edge);
			if (DEBUG_HITBOX)
			{
				DrawCircleAA(box_xc, box_ym, r1, 120, sprite.color, FALSE, .5f);
				DrawBoxAA(box_xl, box_yt, box_xr, box_yb, sprite.color, FALSE, .5f);
				DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, .5f);
				DrawLineAA(box_xr, box_yt, box_xl, box_yb, sprite.color, .5f);
			}
			break;
		}
	case Shape::LINE:
		{
			float r1 = edge;
			// ��
			if (DEBUG_HITBOX)
				size.Render(Vec2{ box_xl, box_yt }, sprite.color, .5f);
			DrawLineAA(box_xl, box_yt, box_xr, box_yb, sprite.color, r1);
			break;
		}
	}
}

// <�I�u�W�F�N�g�T�C�Y�ύX>
void GameObject::SetSize(float scale, float objsize)
{
	sprite.scale = scale;
	size = { objsize * scale, objsize * scale };
}

// <<�t�B�[���h�I�u�W�F�N�g>> ------------------------------------------

// <�t�B�[���h�I�u�W�F�N�g�쐬>
Field::Field(void) :
	GameObject(
		Vec2{ static_cast<float>(SCREEN_CENTER_X), static_cast<float>(SCREEN_CENTER_Y) },
		Vec2{},
		Vec2{ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) }
	)
{
}

// <�t�B�[���h�㉺�Փˏ���>
VerticalSide Field::CollisionVertical(GameObject* obj, Connection connection, Edge edge)
{
	// �q�b�g�T�C�h
	VerticalSide side_hit = VerticalSide::NONE;

	// �R�E���E�㉺�Ǔ����蔻��
	{
		// ���ɉ����ăp�f�B���O�𒲐�
		float padding_top = GetY(VerticalSide::TOP);
		float padding_bottom = GetY(VerticalSide::BOTTOM);
		switch (edge)
		{
		case Edge::INNER:
			padding_top = obj->OffsetY(VerticalSide::BOTTOM, padding_top);
			padding_bottom = obj->OffsetY(VerticalSide::TOP, padding_bottom);
			break;
		case Edge::OUTER:
			padding_top = obj->OffsetY(VerticalSide::TOP, padding_top);
			padding_bottom = obj->OffsetY(VerticalSide::BOTTOM, padding_bottom);
			break;
		}

		// �����蔻��
		if (obj->pos.y < padding_top)
			side_hit = VerticalSide::TOP;
		else if (padding_bottom <= obj->pos.y)
			side_hit = VerticalSide::BOTTOM;

		// �t�B�[���h�̂Ȃ���
		switch (connection)
		{
		case Connection::BARRIER:
			// �ǂɂ��������璲��
			obj->pos.y = GetClamp(obj->pos.y, padding_top, padding_bottom);
			break;
		case Connection::LOOP:
			// �ǂɂ��������烋�[�v
			obj->pos.y = GetLoopRange(obj->pos.y, padding_top, padding_bottom);
			break;
		}
	}

	return side_hit;
}

// <�t�B�[���h���E�Փˏ���>
HorizontalSide Field::CollisionHorizontal(GameObject* obj, Connection connection, Edge edge)
{
	// �q�b�g�T�C�h
	HorizontalSide side_hit = HorizontalSide::NONE;

	// �R�E���E���E�Ǔ����蔻��
	{
		// ���ɉ����ăp�f�B���O�𒲐�
		float padding_left = GetX(HorizontalSide::LEFT);
		float padding_right = GetX(HorizontalSide::RIGHT);
		switch (edge)
		{
		case Edge::INNER:
			padding_left = obj->OffsetX(HorizontalSide::RIGHT, padding_left);
			padding_right = obj->OffsetX(HorizontalSide::LEFT, padding_right);
			break;
		case Edge::OUTER:
			padding_left = obj->OffsetX(HorizontalSide::LEFT, padding_left);
			padding_right = obj->OffsetX(HorizontalSide::RIGHT, padding_right);
			break;
		}

		// �����蔻��
		if (obj->pos.x < padding_left)
			side_hit = HorizontalSide::LEFT;
		else if (padding_right <= obj->pos.x)
			side_hit = HorizontalSide::RIGHT;

		// �t�B�[���h�̂Ȃ���
		switch (connection)
		{
		case Connection::BARRIER:
			// �ǂɂ��������璲��
			obj->pos.x = GetClamp(obj->pos.x, padding_left, padding_right);
			break;
		case Connection::LOOP:
			// �ǂɂ��������烋�[�v
			obj->pos.x = GetLoopRange(obj->pos.x, padding_left, padding_right);
			break;
		}
	}

	return side_hit;
}
