#include "stdafx.h"
#include "PlayerController.h"

#include "Actor/Player.h"
#include "Actor/StateMachine.h"

/** 名前被り等の衝突を防ぐため */
namespace
{
	
}

PlayerController::PlayerController()
{
}


PlayerController::~PlayerController()
{
}

bool PlayerController::Start()
{
	return true;
}


void PlayerController::Update()
{
	auto* targetStateMachine = m_target->GetStateMachine();
	
	// Aボタンで皿を拾う
	//m_target->GetStateMachine()->SetNearFood(true);
	targetStateMachine->ActionButtonA(GetPad()->IsTrigger(enButtonA));

	// Bボタンでダッシュ TODO:ボタンが変わる可能性あり
	targetStateMachine->SetDash(GetPad()->IsPress(enButtonB));
	// 回転
	if (IsInputStickL())
	{
		// 左スティックの方向
		targetStateMachine->SetRotation(ComputeRotation());
		// 左スティックの入力量を取得
		targetStateMachine->SetDirection(GetStickL());
	}
	// スティックの入力量を設定する
	// 0～1の範囲
	targetStateMachine->SetStickLAmount(GetStickL().Length());
}


void PlayerController::Render(RenderContext& rc)
{

}

Vector3 PlayerController::GetStickL()
{
	// 左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = GetPad()->GetLStickXF();
	stickL.y = GetPad()->GetLStickYF();

	// カメラの前方向と右方向のベクトルを取得
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	
	// y方向には移動しない
	forward.y = 0.0f;
	right.y = 0.0f;

	// 左スティックの入力量を加算
	right *= stickL.x;
	forward *= stickL.y;

	Vector3 direction = right + forward;
	// 0～1の範囲に変更
	direction.Normalize();

	return direction;
}


Quaternion PlayerController::ComputeRotation()
{
	// スティックの方向
	Vector3 direction = GetStickL();
	// スティック入力を使ってY軸回転の情報を得る
	Quaternion q;
	q.SetRotationYFromDirectionXZ(direction);

	return q;
}