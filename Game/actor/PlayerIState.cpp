#include "stdafx.h"
#include "Player.h"
#include "PlayerIState.h"
#include "StateMachine.h"
#include "ActorStatus.h"
#include "ActorTypes.h"
#include "Plate.h"


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
	// TODO:後でコメント
	if (m_owner->GetStickLAmount() < 0.01f) {
		return;
	}

	// 移動方向を取得
	const Vector3& moveDirection = m_owner->GetDirection();
	// NOTE:移動速度を後で入れよう
	const Vector3 move = moveDirection * m_owner->GetOwnerStatus()->GetSpeed();
	// 現在の座標を取得
	const Vector3& currentPosition = m_owner->GetPosition();

	// 座標設定
	m_owner->SetPosition(currentPosition + move);
}


void WalkState::Exit()
{
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
	// 現在の座標を取得
	const Vector3& currentPosition = m_owner->GetPosition();

	// 座標設定
	m_owner->SetPosition(currentPosition + move);
}


void DashState::Exit()
{

}




/******************************************/ 


HavePlate::HavePlate(StateMachine* owner)
	:IState(owner)
{
}


HavePlate::~HavePlate()
{

}


void HavePlate::Enter()
{
	Player* player = m_owner->GetOwner();
	FoodPlate* targetFood = m_owner->GetTargetFood();
	targetFood->m_transform.SetParent(&player->m_transform);
	targetFood->SetPosition(m_owner->GetDirection() * 5.0f);
}


void HavePlate::Update()
{
	// 左スティックに少しでも入力量があったら
	if (m_owner->GetStickLAmount() < 0.01f) {
		return;
	}

	// 移動方向を取得
	const Vector3& moveDirection = m_owner->GetDirection();
	// NOTE:移動速度を後で入れよう
	const Vector3 move = moveDirection * m_owner->GetOwnerStatus()->GetSpeed();
	// 現在の座標を取得
	const Vector3& currentPosition = m_owner->GetPosition();

	// 座標設定
	m_owner->SetPosition(currentPosition + move);
}


void HavePlate::Exit()
{
	Player* player = m_owner->GetOwner();
	FoodPlate* targetFood = m_owner->GetTargetFood();
	player->m_transform.RemoveChild(&targetFood->m_transform);

	targetFood->SetPosition(targetFood->m_transform.m_position);
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
	}
}


void ThrowState::Update()
{

}


void ThrowState::Exit()
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




