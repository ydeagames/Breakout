#pragma once

// <�f�o�b�O�p�����蔻��\��>
extern bool DEBUG_HITBOX;

// <�ʒu�֌W>
typedef enum
{
	NONE = 0,
	CENTER_X = 1,				// X����
	LEFT = -2,					// ��
	RIGHT = 2,					// �E
	CENTER_Y = -1,				// Y����
	TOP = -3,					// ��
	BOTTOM = 3					// ��
} ObjectSide;

// <���̈ʒu> 
typedef enum
{
	EDGESIDE_CENTER = 0,		// ���̏�
	EDGESIDE_OUTER = -1,		// ���̊O��
	EDGESIDE_INNER = 1			// ���̓���
} ObjectEdgeSide;

// <���[���h�̂Ȃ���>
typedef enum
{
	CONNECTION_NONE = 0,		// �q����Ȃ��A�����Ȃ���ԂɈړ�
	CONNECTION_BARRIER,			// �ǂ�����A�i�߂Ȃ�
	CONNECTION_LOOP				// ���Α�����o�Ă���
} ObjectConnection;

// <�I�u�W�F�N�g�̌`>
typedef enum
{
	SHAPE_BOX,					// �����`
	SHAPE_CIRCLE,				// �~
	SHAPE_LINE,					// ��
} ObjectShape;

// <�A�j���[�V�����̌���>
typedef enum
{
	ANIMATION_RUNNING,			// �A�j���[�V���������s���̏��
	ANIMATION_FINISHED,			// �A�j���[�V�����Đ��������������
	ANIMATION_IDLE,				// �A�j���[�V�������Ă��Ȃ����
} AnimationState;

// <�e�N�X�`��>
typedef struct
{
	HGRP texture;				// <�e�N�X�`��>
	Vec2 anchor;				// <�e�N�X�`����_>
	Vec2 size;					// <�e�N�X�`���T�C�Y>
	Vec2 center;				// <�e�N�X�`�����S>
} GameTexture;

// <�X�v���C�g�A�j���[�V����>
typedef struct
{
	int frame_start;			// �J�n�t���[���̃C���f�b�N�X
	int frame_end;				// �I���t���[���̃C���f�b�N�X
	int frame_duration;			// �t���[���Ԋu
	int elapsed_time;			// ���݂̃t���[���̌o�ߎ���
	bool loop_flag;				// �A�j���[�V�����̃��[�v
	bool pause_flag;			// �A�j���[�V�����̒�~
	AnimationState result;		// �Ō�̏��
} GameSpriteAnimation;

// <�X�v���C�g�I�u�W�F�N�g>
typedef struct
{
	unsigned int color;			// <�F>
	GameTexture texture;		// <�e�N�X�`��>
	Vec2 size;					// <�T�C�Y>
	int num_columns;			// <1�s������̃t���[����>
	int frame_index;			// <���݂̃t���[���̃C���f�b�N�X>
	Vec2 offset;				// <�I�t�Z�b�g>
	float scale;				// <�X�P�[��>
	float angle;				// <��]>
	GameSpriteAnimation animation;	// <�X�v���C�g�A�j���[�V����>
} GameSprite;

// <�Q�[���I�u�W�F�N�g>
typedef struct
{
	Vec2 pos;					// <�ʒu>
	Vec2 vel;					// <���x>
	Vec2 size;					// <�傫��>
	ObjectShape shape;			// <�`>
	GameSprite sprite;			// <�X�v���C�g>
	bool fill;					// <�h��Ԃ�>
	float edge;					// <��>
	ObjectConnection sprite_connection;	// <�X�v���C�g�̂Ȃ���>
	bool alive;					// <�\�����>
	int state;					// <���>
	int type;					// <�^�C�v>
	Timer count;			// <�J�E���^>
} GameObject;

// <�e�N�X�`��>
#define TEXTURE_MISSING -1		// �e�N�X�`����������܂���
#define TEXTURE_NONE -2			// �e�N�X�`���Ȃ�

// <<�e�N�X�`��>> ------------------------------------------------------

// <�e�N�X�`���쐬>
GameTexture GameTexture_Create(HGRP texture, Vec2 anchor, Vec2 size);

// <�e�N�X�`���Ȃ�>
GameTexture GameTexture_CreateNone();

// <<�X�v���C�g�A�j���[�V����>> ----------------------------------------

// <�X�v���C�g�A�j���[�V�����쐬>
GameSpriteAnimation GameSpriteAnimation_Create(int frames_start, int frames_end, int frame_duration, bool pause = FALSE);

// <�X�v���C�g�A�j���[�V�����Ȃ�>
GameSpriteAnimation GameSpriteAnimation_CreateNone();

// <�X�v���C�g�A�j���[�V�����X�V>
AnimationState GameSpriteAnimation_Update(GameSprite* obj);

// <<�X�v���C�g>> ------------------------------------------------------

// <�X�v���C�g�쐬>
GameSprite GameSprite_Create(GameTexture texture, float scale = 1, float angle = 0);

// <�X�v���C�g�Ȃ�>
GameSprite GameSprite_CreateNone();

// <�X�v���C�g�X�V>
void GameSprite_SetFrame(GameSprite* sprite, int frame);

// <�X�v���C�g�`��>
void GameSprite_Render(const GameSprite* sprite, const Vec2* pos);

// <<�e�B�b�N>>

// <�I�u�W�F�N�g�쐬>
void GameTick_Update(void);

// <<�I�u�W�F�N�g>>

// <�I�u�W�F�N�g�쐬>
GameObject GameObject_Create(Vec2 pos = {}, Vec2 vel = {}, Vec2 size = {});

// <���I�u�W�F�N�g�쐬>
GameObject GameObject_CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel = {});

// <�I�u�W�F�N�g�폜>
void GameObject_Dispose(GameObject* obj);

// <�I�u�W�F�N�g�m�F>
bool GameObject_IsAlive(const GameObject* obj);

// <�I�u�W�F�N�g���W�X�V>
void GameObject_UpdatePosition(GameObject* obj);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetX(const GameObject* obj, ObjectSide side, float pos = 0.f, float margin = 0.f);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetY(const GameObject* obj, ObjectSide side, float pos = 0.f, float margin = 0.f);

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetX(const GameObject* obj, ObjectSide side, float margin = 0.f);

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetY(const GameObject* obj, ObjectSide side, float margin = 0.f);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetRawX(const GameObject* obj, ObjectSide side, float pos, float padding = 0.f);

// <�I�u�W�F�N�gX�I�t�Z�b�g>
float GameObject_OffsetRawY(const GameObject* obj, ObjectSide side, float pos, float padding = 0.f);

// <�I�u�W�F�N�gX�ʒu�Q�b�g>
float GameObject_GetRawX(const GameObject* obj, ObjectSide side, float padding = 0.f);

// <�I�u�W�F�N�gY�ʒu�Q�b�g>
float GameObject_GetRawY(const GameObject* obj, ObjectSide side, float padding = 0.f);

// <�I�u�W�F�N�g�`��>
void GameObject_Render(const GameObject* obj, const Vec2* translate = &Vec2{});

// <�e�I�u�W�F�N�g�T�C�Y�ύX>
void GameObject_SetSize(GameObject* obj, float scale, float size = 10);

// <<�t�B�[���h�I�u�W�F�N�g>>

// <�t�B�[���h�I�u�W�F�N�g�쐬>
GameObject GameObject_Field_Create(void);

// <�t�B�[���h�㉺�Փˏ���>
ObjectSide GameObject_Field_CollisionVertical(const GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge);

// <�t�B�[���h���E�Փˏ���>
ObjectSide GameObject_Field_CollisionHorizontal(const GameObject* field, GameObject* obj, ObjectConnection connection, ObjectEdgeSide edge);