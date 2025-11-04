#include "stdafx.h"
#include "Player.h"
#include "PlayerIState.h"
#include "StateMachine.h"
#include "ActorStatus.h"
#include "ActorTypes.h"
#include "Plate.h"
#include "sound/SoundManager.h"
#include "effect/EffectManager.h"


namespace
{
	const float PLAYER_MOVE_SPEED = 2.0f; //移動速度
}


WalkState::WalkState(StateMachine* owner)
	: IState(owner)
{
}


WalkState::~WalkState()
{

}


void WalkState::Enter()
{
	m_owner->PlayAnimation(static_cast<uint8_t>(PlayerAnimationType::Walk));
}


void WalkState::Update()
{
	if (m_owner->GetStickLAmount() < 0.01f) {
		return;
	}

	// 移動方向を取得
	const Vector3& moveDirection = m_owner->GetDirection();
	// NOTE:移動速度を後で入れよう
	const Vector3 move = moveDirection * m_owner->GetOwnerStatus()->GetSpeed();
	// 座標設定
	m_owner->SetMoveVector(move);
}


void WalkState::Exit()
{
	// 移動終わり
	m_owner->SetMoveVector(Vector3::Zero);
}




/******************************************/ 


DashState::DashState(StateMachine* owner)
	: IState(owner)
{
}


DashState::~DashState()
{

}


void DashState::Enter()
{
	m_owner->PlayAnimation(static_cast<uint8_t>(PlayerAnimationType::Idle));
}


void DashState::Update()
{
	// 左スティックの入力量が小さい場合は処理をしない
	if (m_owner->GetStickLAmount() < 0.01f) {
		return;
	}

	// 移動方向を取得
	const Vector3& moveDirection = m_owner->GetDirection();
	// ダッシュスピードを計算
	const float moveSpeed = m_owner->GetOwnerStatus()->GetSpeed();
	const float dashSpeed = m_owner->GetOwnerStatus()->GetDashSpeed();
	const float moveDashSpeed  = moveSpeed * dashSpeed;
	// 移動方向にどれだけ進むかを求める
	const Vector3 move = moveDirection * moveDashSpeed;
	// 座標設定
	m_owner->SetMoveVector(move);

	//エフェクトを生成
	EffectManager::Get().PlayEffect(enEffectKind_Dash, m_owner->GetPosition(), m_owner->GetRotation(), Vector3(20.0f, 20.0f, 20.0f));
}


void DashState::Exit()
{
	// 移動終わり
	m_owner->SetMoveVector(Vector3::Zero);
}




/******************************************/ 


HavePlateState::HavePlateState(StateMachine* owner)
	:IState(owner)
{
}


HavePlateState::~HavePlateState()
{
}


void HavePlateState::Enter()
{
	// プレイヤーの情報を取得
	Player* player = m_owner->GetOwner();
	// 食べ物の情報を取得
	FoodPlate* targetFood = m_owner->GetTargetFood();
	// 食べ物をプレイヤーの子にする
	targetFood->m_transform.SetParent(&player->m_transform);
	// 食べ物をプレイヤーの前に配置 (持っている表現)
	targetFood->SetPosition(m_owner->GetDirection() * 10.0f);

	// 持った時のSE再生
	SoundManager::Get().PlaySE(enSoundKind_Has);
}


void HavePlateState::Update()
{
	// 左スティックに少しでも入力量があったら
	if (m_owner->GetStickLAmount() < 0.01f) {
		return;
	}

	// 移動方向を取得
	const Vector3& moveDirection = m_owner->GetDirection();
	// NOTE:移動速度を後で入れよう
	const Vector3 move = moveDirection * m_owner->GetOwnerStatus()->GetSpeed();
	// 座標設定
	m_owner->SetMoveVector(move);
}


void HavePlateState::Exit()
{
	Player* player = m_owner->GetOwner();
	FoodPlate* targetFood = m_owner->GetTargetFood();
	if (targetFood) {
		player->m_transform.RemoveChild(&targetFood->m_transform);
		targetFood->SetPosition(targetFood->m_transform.m_position);
	}
	// 移動終わり
	m_owner->SetMoveVector(Vector3::Zero);
}	




/********************************************/


ThrowState::ThrowState(StateMachine* owner)
	:IState(owner)
{

}


ThrowState::~ThrowState()
{

}


void ThrowState::Enter()
{
	// 投げる
	if (m_owner->GetTargetFood())
	{
		FoodPlate* targetFood = m_owner->GetTargetFood();
		targetFood->Throw(m_owner->GetDirection());
		m_owner->SetNearFood(false);
		m_owner->SetForwardFood(false);

		// 投げた時にSEを再生
		SoundManager::Get().PlaySE(enSoundKind_Throw);
	}

}


void ThrowState::Update()
{

}


void ThrowState::Exit()
{

}




/********************************************/


CoockingState::CoockingState(StateMachine* owner)
	: IState(owner)
{
}


CoockingState::~CoockingState()
{
}


void CoockingState::Enter()
{
	// 投げる
	FoodPlate* targetFood = m_owner->GetTargetFood();
	K2_ASSERT(targetFood, "食べ物を持っていません。\n");
	if (targetFood)
	{
		// 料理済みにする
		targetFood->ChangedCoocke();

		// 切ったときにSEを再生
		SoundManager::Get().PlaySE(enSoundKind_Cut);
	}
}


void CoockingState::Update()
{
}


void CoockingState::Exit()
{
}




/********************************************/


IdleState::IdleState(StateMachine* owner)
	: IState(owner)
{

}


IdleState::~IdleState()
{

}


void IdleState::Enter()
{

}


void IdleState::Update()
{

}


void IdleState::Exit()
{

}




