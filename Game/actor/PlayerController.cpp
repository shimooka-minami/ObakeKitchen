#include "stdafx.h"
#include "PlayerController.h"

#include "Actor/Player.h"
#include "Actor/StateMachine.h"

/** 名前被り等の衝突を防ぐため */
namespace
{
	inline bool IsInputStickL()
	{
		// 左スティックの入力があるかどうかを判定
		if ((fabsf(g_pad[0]->GetLStickXF()) >= FLT_EPSILON) || (fabsf(g_pad[0]->GetLStickYF()) >= FLT_EPSILON))
		{
			return true;
		}
		return false;
	}
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

	// 左スティックの入力量を取得
	targetStateMachine->SetDirection(GetStickL());
	// Bボタンでダッシュ TODO:ボタンが変わる可能性あり
	targetStateMachine->SetDash(g_pad[0]->IsPress(enButtonB));
	// 回転
	if (IsInputStickL()) {
		// 左スティックが入力されたら
		targetStateMachine->SetRotation(ComputeRotation());
	}
}


void PlayerController::Render(RenderContext& rc)
{

}

Vector3 PlayerController::GetStickL() const
{
	// 左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// カメラの前方向と右方向のベクトルを取得
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	
	// y方向には移動しない
	forward.y = 0.0f;
	right.y = 0.0f;

	// 左スティックの入力量を加算
	right *= stickL.x;
	forward *= stickL.y;

	return right + forward;
}


Quaternion PlayerController::ComputeRotation() const
{
	// スティックの方向
	Vector3 direction = GetStickL();
	// 0～1の範囲に変更
	direction.Normalize();

	// スティック入力を使ってY軸回転の情報を得る
	Quaternion q;
	q.SetRotationYFromDirectionXZ(direction);

	return q;
}

