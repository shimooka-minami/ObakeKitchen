#include "stdafx.h"
#include "CollisionManager.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"
#include "actor/Plate.h"


CollisionHitManager* CollisionHitManager::m_instance = nullptr;


void CollisionHitManager::Update()
{
	// @todo for test 当たったら
	if (m_foodPlate->GetCollisionObject()->IsHit(*m_player->GetCharacterController()))
	{
		// プレイヤーの前に皿がない場合
		if (!m_player->GetStateMachine()->IsForwardFood()) 
		{
			// 近くにある（プレイヤーと皿が接触しているときの処理）
			m_player->GetStateMachine()->SetNearFood(true);

			// プレイヤーと皿が接触したときの処理
			//m_foodPlate->Throw(m_player->GetStateMachine()->GetDirection());

			Vector3 playerDirection = m_player->GetStateMachine()->GetDirection();
			Vector3 foodDirection = m_foodPlate->m_transform.m_position - m_player->m_transform.m_position;
			foodDirection.Normalize();

			// 内積を入れる変数
			float dot;
			// 内積の計算 プレイヤーからフードの方向
			dot = playerDirection.Dot(foodDirection);
			// 内積からacosで角度(円周率)を求めている
			float angle = acos(dot);

			// 円周率を角度に変換したとき、プレイヤーとフードの角度が30度以上なら
			m_player->GetStateMachine()->SetForwardFood(angle <= Math::DegToRad(30.0f));

			// フードクラスをターゲットに設定
			m_player->GetStateMachine()->SetTargetFood(m_foodPlate);
		}
	}
}