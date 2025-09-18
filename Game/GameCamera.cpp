#include "stdafx.h"
#include "GameCamera.h"

#include "Actor/Player.h"

const float CAMERA_POS_Y = 500.0f; //カメラのY座標
const float CAMERA_POS_Z = -1000.0f; //カメラのZ座標

const float CAMERA_NEAR_CLIP = 1.0f; //ニアクリップ
const float CAMERA_FAR_CLIP = 10000.0f; //ファークリップ

const float CAMERA_TARGET_POS_Y = 100.0f; //注視点のY座標

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(0.0f, CAMERA_POS_Y, CAMERA_POS_Z);

	//プレイヤーを取得
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(CAMERA_NEAR_CLIP);
	g_camera3D->SetFar(CAMERA_FAR_CLIP);

	return true;
}

//カメラを更新
void GameCamera::Update()
{
	//注視点を計算 //画面の固定
	Vector3 target;
	//注視点を上にする (俯瞰)
	target.y += CAMERA_TARGET_POS_Y;
	//カメラの座標
	Vector3 tpCameraPos = m_toCameraPos;
	//注視点+カメラの視点を設定
	Vector3 pos = target + tpCameraPos;

	//メインカメラに注視点と視点を設定
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	g_camera3D->Update();
}

void GameCamera::Render(RenderContext&rc)
{
}