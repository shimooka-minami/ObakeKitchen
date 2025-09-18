#include "stdafx.h"
#include "PlayerIState.h"

const float PLAYER_MOVE_SPEED = 2.0f; //�ړ����x

PlayerIState::PlayerIState()
{
}

PlayerIState::~PlayerIState()
{
}

bool PlayerIState::Start()
{
	//�A�j���[�V����
	m_animationClips[enPlayerAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enPlayerAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enPlayerAnimClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enPlayerAnimClip_Walk].SetLoopFlag(true);

	return true;
}

void PlayerIState::Update()
{

}

void PlayerIState::PlayerMove()
{
	//���X�e�B�b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickXF();

	//�J�����̑O�����ƉE�����̃x�N�g�����擾
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ����Z����(�Ƃ肠����100.0f)
	right *= stickL.x * 100.0f;
	forward *= stickL.y * 100.0f;

	//�ړ����x�ɃX�e�B�b�N���͗ʂ����Z
	m_moveSpeed += right + forward;

	//���W
	
	
}

void PlayerIState::Render(RenderContext&rc)
{

}


