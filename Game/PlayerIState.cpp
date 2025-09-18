#include "stdafx.h"
#include "PlayerIState.h"

const float PLAYER_MOVE_SPEED = 2.0f; //移動速度

PlayerIState::PlayerIState()
{
}

PlayerIState::~PlayerIState()
{
}

bool PlayerIState::Start()
{
	//アニメーション
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
	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickXF();

	//カメラの前方向と右方向のベクトルを取得
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量を加算する(とりあえず100.0f)
	right *= stickL.x * 100.0f;
	forward *= stickL.y * 100.0f;

	//移動速度にスティック入力量を加算
	m_moveSpeed += right + forward;

	//座標
	
	
}

void PlayerIState::Render(RenderContext&rc)
{

}


