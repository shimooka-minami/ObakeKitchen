#include "stdafx.h"
#include "StateMachine.h"

#include "Actor/Player.h"
#include "Actor/PlayerIState.h"


StateMachine::StateMachine()
{
	//ステートの生成
	AddState<IdleState>(enPlayerIdle);
	AddState<DashState>(enPlayerDash);
	AddState<WalkState>(enPlayerWalk);
	AddState<HavePlateState>(enPlayerHavePlate);
	AddState<ThrowState>(enPlayerThrow);
	AddState<CoockingState>(enPlayerCoocking);
	K2_ASSERT(ARRAYSIZE(m_stateList) == enPlayerNum, "AddStateを呼んでください");

	//初期ステート
	m_currentState = m_stateList[enPlayerIdle];
}


StateMachine::~StateMachine()
{
	for (auto* it : m_stateList) {
		delete it;
		it = nullptr;
	}
}


void StateMachine::Update()
{
	//ステートの切り替え
	ChangeState();
	//ステートの更新
	m_currentState->Update();

	// １フレームだけの情報を初期化する
	m_isInCookingSpace = false;
}


void StateMachine::ChangeState()
{
	// 切り替え先のステートを取得
	IState* nextState = GetChangeState();
	//ステートが切り替わった(nullptrじゃない)時・今のステートがnextStateと同じ数字ではない時
	if (nextState != nullptr && m_currentState != nextState) {
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
	//
	// ステートの切り替わり
	//

	// 皿を持っている状態なら
	if (IsEqualCurrentState(enPlayerHavePlate)) {
		// 料理する状態に変わるかチェック
		if (CanChangeCooking()) {
			return m_stateList[enPlayerCoocking];
		}
		// 投げる状態に変わるかチェック
		if (CanChangeThrow()) {
			return m_stateList[enPlayerThrow];
		}
		return nullptr;
	}

	// その他
	if (ChangeHavePlate()) {
		return m_stateList[enPlayerHavePlate];
	}
	if (CanChangeDash()) {
		return m_stateList[enPlayerDash];
	}
	if (CanChangeWalk()) {
		return m_stateList[enPlayerWalk];
	}
	return m_stateList[enPlayerIdle];
}


bool StateMachine::CanChangeWalk() const
{
	if (m_stickLAmount > 0.01f) {
		return true;
	}
	return false;
}


bool StateMachine::CanChangeDash() const
{
	if (m_isDash && m_direction.Length() > 0.01f) {
		return true;
	}
	return false;
}


bool StateMachine::ChangeHavePlate() const
{
	// 皿が持てる状態か
	bool canHavePlateState = false;
	if (IsEqualCurrentState(enPlayerIdle)) {
		canHavePlateState = true;
	}
	if (IsEqualCurrentState(enPlayerWalk)) {
		canHavePlateState = true;
	}
	if (IsEqualCurrentState(enPlayerDash)) {
		canHavePlateState = true;
	}
	if (!canHavePlateState) {
		return false;
	}

	// 皿の近くにいて、皿が目の前にあって、皿を持っていないときに皿を持ちたい
	if (!m_isNearFood) {
		return false;
	}
	if (!m_isForwardFood) {
		return false;
	}

	// 上記の条件を満たしていて、Aボタンが押されたら皿を持つ
	if (m_actionButtonA) {
		return true;
	}

	return false;
}


bool StateMachine::CanChangeThrow() const
{
	if (!IsEqualCurrentState(enPlayerHavePlate)) {
		return false;
	}
	// Aボタンが押されたら皿を投げる
	if (m_actionButtonA) {
		return true;
	}
	return false;
}


bool StateMachine::CanChangeCooking() const
{
	if (!m_isInCookingSpace){
		return false;
	}
	// Aボタンを押したら
	if (m_actionButtonA)
	{
		return true;
	}
	// 料理スペースにいるけど、Aボタンを押していないとき
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