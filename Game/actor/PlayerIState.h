#pragma once


class StateMachine;


/**
 * 状態の基底クラス
 */
class IState
{
protected:
	StateMachine* m_owner; //状態を持っているオーナー(状態を持っているクラスのポインタ)

public:
	IState(StateMachine* owner) : m_owner(owner) {}

	/** 状態が切り替わった時に一度だけ呼ばれる(コンストラクタのように最初によばれるもの) */
	virtual void Enter() = 0;
	/** 毎フレーム更新される */
	virtual void Update() = 0;
	/** 状態が切り替わる時に一度だけ呼ばれる(デストラクタのように最後に呼ばれる) */
	virtual void Exit() = 0;
};




class WalkState : public IState
{
public:
	WalkState(StateMachine* owner);
	~WalkState();

	void Enter() override;
	void Update() override;
	void Exit() override;
};


class DashState : public IState
{
public:
	DashState(StateMachine* owner);
	~DashState();

	void Enter() override;
	void Update() override;
	void Exit() override;
};


class HavePlate : public IState
{
public:
	HavePlate(StateMachine* owner);
	~HavePlate();

	void Enter() override;
	void Update() override;
	void Exit() override;
};




class ThrowState : public IState
{
public:
	ThrowState(StateMachine* owner);
	~ThrowState();

	void Enter() override;
	void Update() override;
	void Exit() override;
};




class IdleState : public IState
{ 
public:
	IdleState(StateMachine* owner);
	~IdleState();

	void Enter() override;
	void Update() override;
	void Exit() override;
};