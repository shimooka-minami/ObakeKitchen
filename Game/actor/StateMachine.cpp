#include "stdafx.h"
#include "StateMachine.h"

#include "Actor/Player.h"
#include "Actor/PlayerIState.h"


StateMachine::StateMachine()
{
	//�X�e�[�g�̐���
	m_stateList[enPlayerIdle] = new IdleState(this);
	m_stateList[enPlayerDash] = new DashState(this);
	m_stateList[enPlayerWalk] = new WalkState(this);

	//�����X�e�[�g
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
	//�X�e�[�g�̐؂�ւ�
	ChangeState();
	//�X�e�[�g�̍X�V
	m_currentState->Update();
}


void StateMachine::ChangeState()
{
	// �؂�ւ���̃X�e�[�g���擾
	IState* nextState = GetChangeState();
	//�X�e�[�g���؂�ւ����(nullptr����Ȃ�)���E���̃X�e�[�g��nextState�Ɠ��������ł͂Ȃ���
	if (nextState != nullptr && m_currentState != nextState)
	{
		//���̃X�e�[�g���I��
		m_currentState->Exit();
		//�V�����X�e�[�g�ɕύX
		m_currentState = nextState;
		//�V�����X�e�[�g���J�n
		m_currentState->Enter();
	}
}


IState* StateMachine::GetChangeState() const
{
	//�X�e�[�g�̐؂�ւ��
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