#pragma once
#include "Character.h"


class StateMachine;


class Player : public Character
{
private:
	std::unique_ptr<StateMachine> m_stateMachine;


public:
	Player();
	~Player();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;


public:
	/** ステートマシンの取得 */
	StateMachine* GetStateMachine() { return m_stateMachine.get(); }


public:
	PlayerStatus* GetPlayerStatus() { return dynamic_cast<PlayerStatus*>(m_status); }
};

