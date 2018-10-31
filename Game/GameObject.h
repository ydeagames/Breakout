#pragma once

// <�f�o�b�O�p�����蔻��\��>
extern bool DEBUG_HITBOX;

// <���ʒu�֌W>
enum class HorizontalSide
{
	NONE,
	CENTER,						// X����
	LEFT,						// ��
	RIGHT,						// �E
};

// <�c�ʒu�֌W>
enum class VerticalSide
{
	NONE,
	CENTER,						// Y����
	TOP,						// ��
	BOTTOM,						// ��
};

// <���̈ʒu> 
enum class Edge
{
	CENTER,						// ���̏�
	OUTER,						// ���̊O��
	INNER,						// ���̓���
};

// <���[���h�̂Ȃ���>
enum class Connection
{
	NONE,						// �q����Ȃ��A�����Ȃ���ԂɈړ�
	BARRIER,					// �ǂ�����A�i�߂Ȃ�
	LOOP,						// ���Α�����o�Ă���
};

// <�I�u�W�F�N�g�̌`>
enum class Shape
{
	BOX,						// �����`
	CIRCLE,						// �~
	LINE,						// ��
};

// <�A�j���[�V�����̌���>
enum class AnimationState
{
	RUNNING,					// �A�j���[�V���������s���̏��
	FINISHED,					// �A�j���[�V�����Đ��������������
	IDLE,						// �A�j���[�V�������Ă��Ȃ����
};

// <�e�N�X�`��>
class GameTexture
{
public:
	HGRP texture;				// <�e�N�X�`��>
	Vec2 anchor;				// <�e�N�X�`����_>
	Vec2 size;					// <�e�N�X�`���T�C�Y>
	Vec2 center;				// <�e�N�X�`�����S>
public:
	static constexpr int TEXTURE_MISSING = -1;		// �e�N�X�`����������܂���
	static constexpr int TEXTURE_NONE = -2;			// �e�N�X�`���Ȃ�

	// <�e�N�X�`���쐬>
	GameTexture(HGRP texture, Vec2 anchor, Vec2 size);

	// <�e�N�X�`���Ȃ�>
	GameTexture();
};

// <�X�v���C�g�I�u�W�F�N�g>
class GameSprite
{
public:
	unsigned int color;			// <�F>
	GameTexture texture;		// <�e�N�X�`��>
	Vec2 size;					// <�T�C�Y>
	int num_columns;			// <1�s������̃t���[����>
	int frame_index;			// <���݂̃t���[���̃C���f�b�N�X>
	Vec2 offset;				// <�I�t�Z�b�g>
	float scale;				// <�X�P�[��>
	float angle;				// <��]>
public:
	GameSprite(GameTexture texture, float scale = 1, float angle = 0);

	// <�X�v���C�g�Ȃ�>
	GameSprite();

	virtual ~GameSprite() {};

	// <�X�v���C�g�X�V>
	void SetFrame(int frame);

	// <�X�v���C�g�`��>
	void Render(const Vec2* pos);
};

// <�X�v���C�g�A�j���[�V����>
class GameSpriteAnimation : public GameSprite
{
public:
	int frame_start;			// �J�n�t���[���̃C���f�b�N�X
	int frame_end;				// �I���t���[���̃C���f�b�N�X
	int frame_duration;			// �t���[���Ԋu
	int elapsed_time;			// ���݂̃t���[���̌o�ߎ���
	bool loop_flag;				// �A�j���[�V�����̃��[�v
	bool pause_flag;			// �A�j���[�V�����̒�~
	AnimationState result;		// �Ō�̏��
public:
	// <�X�v���C�g�A�j���[�V�����쐬>
	GameSpriteAnimation(GameTexture texture, int frames_start, int frames_end, int frame_duration, float scale = 1, float angle = 0, bool pause = false);

	// <�X�v���C�g�A�j���[�V�����Ȃ�>
	GameSpriteAnimation();

	virtual ~GameSpriteAnimation() {};

	// <�X�v���C�g�A�j���[�V�����X�V>
	AnimationState Update();
};

// <�Q�[���I�u�W�F�N�g>
class GameObject
{
public:
	Vec2 pos;					// <�ʒu>
	Vec2 vel;					// <���x>
	Vec2 size;					// <�傫��>
	Shape shape;				// <�`>
	GameSprite sprite;			// <�X�v���C�g>
	bool fill;					// <�h��Ԃ�>
	float edge;					// <��>
	Connection sprite_connection;	// <�X�v���C�g�̂Ȃ���>
	bool alive;					// <�\�����>
	int state;					// <���>
	int type;					// <�^�C�v>
	Timer count;			// <�J�E���^>
public:
	// <�I�u�W�F�N�g�쐬>
	GameObject(Vec2 pos = {}, Vec2 vel = {}, Vec2 size = {});

	virtual ~GameObject() {};

	// <���I�u�W�F�N�g�쐬>
	static GameObject CreateLine(Vec2 pos1, Vec2 pos2, Vec2 vel = {});

	// <�I�u�W�F�N�g�폜>
	void Dispose();

	// <�I�u�W�F�N�g�m�F>
	bool IsAlive();

	// <�I�u�W�F�N�g���W�X�V>
	void UpdatePosition();

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetX(HorizontalSide side, float pos = 0.f, float margin = 0.f);

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetY(VerticalSide side, float pos = 0.f, float margin = 0.f);

	// <�I�u�W�F�N�gX�ʒu�Q�b�g>
	float GetX(HorizontalSide side, float margin = 0.f);

	// <�I�u�W�F�N�gY�ʒu�Q�b�g>
	float GetY(VerticalSide side, float margin = 0.f);

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetRawX(HorizontalSide side, float pos, float padding = 0.f);

	// <�I�u�W�F�N�gX�I�t�Z�b�g>
	float OffsetRawY(VerticalSide side, float pos, float padding = 0.f);

	// <�I�u�W�F�N�gX�ʒu�Q�b�g>
	float GetRawX(HorizontalSide side, float padding = 0.f);

	// <�I�u�W�F�N�gY�ʒu�Q�b�g>
	float GetRawY(VerticalSide side, float padding = 0.f);

	// <�I�u�W�F�N�g�`��>
	void Render(const Vec2* translate = &Vec2{});

	// <�e�I�u�W�F�N�g�T�C�Y�ύX>
	void SetSize(float scale, float size = 10);
};

class Field : GameObject
{
public:
	// <�t�B�[���h�I�u�W�F�N�g�쐬>
	Field(void);

	virtual ~Field() {};

	// <�t�B�[���h�㉺�Փˏ���>
	VerticalSide CollisionVertical(GameObject* obj, Connection connection, Edge edge);

	// <�t�B�[���h���E�Փˏ���>
	HorizontalSide CollisionHorizontal(GameObject* obj, Connection connection, Edge edge);
};

// <�I�u�W�F�N�g�쐬>
void GameTick_Update(void);

