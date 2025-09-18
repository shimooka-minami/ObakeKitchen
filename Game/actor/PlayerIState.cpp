#include "stdafx.h"
#include "PlayerIState.h"
#include "StateMachine.h"
#include "ActorStatus.h"
#include "ActorTypes.h"


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