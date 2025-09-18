#include "stdafx.h"
#include "GameCamera.h"

#include "Actor/Player.h"

const float CAMERA_POS_Y = 500.0f; //�J������Y���W
const float CAMERA_POS_Z = -1000.0f; //�J������Z���W

const float CAMERA_NEAR_CLIP = 1.0f; //�j�A�N���b�v
const float CAMERA_FAR_CLIP = 10000.0f; //�t�@�[�N���b�v

const float CAMERA_TARGET_POS_Y = 100.0f; //�����_��Y���W

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(0.0f, CAMERA_POS_Y, CAMERA_POS_Z);

	//�v���C���[���擾
	m_player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
	g_camera3D->SetNear(CAMERA_NEAR_CLIP);
	g_camera3D->SetFar(CAMERA_FAR_CLIP);

	return true;
}

//�J�������X�V
void GameCamera::Update()
{
	//�����_���v�Z //��ʂ̌Œ�
	Vector3 target;
	//�����_����ɂ��� (����)
	target.y += CAMERA_TARGET_POS_Y;
	//�J�����̍��W
	Vector3 tpCameraPos = m_toCameraPos;
	//�����_+�J�����̎��_��ݒ�
	Vector3 pos = target + tpCameraPos;

	//���C���J�����ɒ����_�Ǝ��_��ݒ�
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V
	g_camera3D->Update();
}

void GameCamera::Render(RenderContext&rc)
{
}