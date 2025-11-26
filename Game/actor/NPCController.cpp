#include "stdafx.h"
#include "NPCController.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"

/** 名前被り等の衝突を防ぐため */
namespace
{
	// @todo for test
	constexpr float PLAYER_MOVE_SPEED = 3.0f; // 移動速度
}

NPCController::NPCController()
{
}


NPCController::~NPCController()
{
}

bool NPCController::Start()
{
	return true;
}


void NPCController::Update()
{
	auto* targetStateMachine = m_target->GetStateMachine();

	// 経過時間
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();

	// @todo for test とりあえず左右移動
	constexpr float LEFT_MOVE_TIME = 2.0f;
	if (m_elapsedTime <= LEFT_MOVE_TIME)
	{
		m_target->GetStateMachine()->SetDirection(Vector3::Left);
		m_target->GetStateMachine()->SetStickLAmount(1.0f);
		return;
	}
	constexpr float RIGHT_MOVE_TIME = 4.0f;
	if (m_elapsedTime <= RIGHT_MOVE_TIME)
	{
		m_target->GetStateMachine()->SetDirection(Vector3::Right);
		m_target->GetStateMachine()->SetStickLAmount(1.0f);
		return;
	}

	m_elapsedTime = 0.0f;
}


void NPCController::Render(RenderContext& rc)
{

}

//Vector3 NPCController::GetStickL()
//{
//	// 左スティックの入力量を取得
//	Vector3 stickL;
//	stickL.x = GetPad()->GetLStickXF();
//	stickL.y = GetPad()->GetLStickYF();
//
//	// カメラの前方向と右方向のベクトルを取得
//	Vector3 forward = g_camera3D->GetForward();
//	Vector3 right = g_camera3D->GetRight();
//	
//	// y方向には移動しない
//	forward.y = 0.0f;
//	right.y = 0.0f;
//
//	// 左スティックの入力量を加算
//	right *= stickL.x;
//	forward *= stickL.y;
//
//	Vector3 direction = right + forward;
//	// 0～1の範囲に変更
//	direction.Normalize();
//
//	return direction;
//}

//
//Quaternion NPCController::ComputeRotation()
//{
//	// スティックの方向
//	Vector3 direction = GetStickL();
//	// スティック入力を使ってY軸回転の情報を得る
//	Quaternion q;
//	q.SetRotationYFromDirectionXZ(direction);
//
//	return q;
//}