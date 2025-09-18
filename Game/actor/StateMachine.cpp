#include "stdafx.h"
#include "StateMachine.h"

#include "Actor/Player.h"
#include "Actor/PlayerIState.h"


StateMachine::StateMachine()
{
	//ステートの生成
	m_stateList[enPlayerIdle] = new IdleState(this);
	m_stateList[enPlayerDash] = new DashState(this);
	m_stateList[enPlayerWalk] = new WalkState(this);

	//初期ステート
	m_currentState = m_stateList[enPlayerIdle];
}


StateMachine::~StateMachine()
{
	for (auto it : m_stateList) 
	{
		delete it;
	}
}


void StateMachine::Update()
{
	//ステートの切り替え
	ChangeState();
	//ステートの更新
	m_currentState->Update();
}


void StateMachine::ChangeState()
{
	// 切り替え先のステートを取得
	IState* nextState = GetChangeState();
	//ステートが切り替わった(nullptrじゃない)時・今のステートがnextStateと同じ数字ではない時
	if (nextState != nullptr && m_currentState != nextState)
	{
		//今のステートを終了
		m_currentState->Exit();
		//新しいステートに変更
		m_currentState = nextState;
		//新しいステートを開始
		m_currentState->Enter();
	}
}


IState* StateMachine::GetChangeState() const
{
	//ステートの切り替わり
	if (CanChangeDash())
	{
		return m_stateList[enPlayerDash];
	}
	if (CanChangeWalk())
	{
		return m_stateList[enPlayerWalk];
	}
	return m_stateList[enPlayerIdle];
}


bool StateMachine::CanChangeWalk() const
{
	if (m_direction.Length() > 0.01f)
	{
		return true;
	}
	return false;
}


bool StateMachine::CanChangeDash() const
{
	if (m_isDash && m_direction.Length() > 0.01f)
	{
		return true;
	}
	return false;
}


void StateMachine::Setup(Player* owner)
{
	m_owner = owner;
	m_ownerStatus = owner->GetPlayerStatus();
}


void StateMachine::PlayAnimation(const int animationIndex)
{
	m_owner->GetModelRender()->PlayAnimation(animationIndex);
}