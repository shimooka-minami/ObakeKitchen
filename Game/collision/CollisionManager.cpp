#include "stdafx.h"
#include "CollisionManager.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"
#include "actor/Plate.h"


CollisionHitManager* CollisionHitManager::m_instance = nullptr;


CollisionHitManager::CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


CollisionHitManager::~CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


void CollisionHitManager::Update()
{
	// ヒットするオブジェクトのペアを作る
	const uint32_t colSize = static_cast<uint32_t>(m_collisionInfoList.size());
	for (uint32_t i = 0; i < colSize; ++i) {
		for (uint32_t j = i; j < colSize; ++j) {
			CollisionInfo* infoA = &m_collisionInfoList[i];
			CollisionInfo* infoB = &m_collisionInfoList[j];

			if(infoA->m_collision->IsHit(infoB->m_collision) || infoB->m_collision->IsHit(infoA->m_collision))
			{
				m_collisionPairList.push_back(CollisionPair(infoA, infoB));
			}
		}
	}
	// ペアでかぶった情報があれば省く
	for(auto it = m_collisionPairList.begin(); it != m_collisionPairList.end(); )
	{
		auto nextIt = std::next(it);
		bool erased = false;
		for(auto jt = nextIt; jt != m_collisionPairList.end(); ++jt)
		{
			if((it->m_infoA == jt->m_infoA && it->m_infoB == jt->m_infoB) ||
			   (it->m_infoA == jt->m_infoB && it->m_infoB == jt->m_infoA))
			{
				it = m_collisionPairList.erase(it);
				erased = true;
				break;
			}
		}
		if(!erased)
		{
			++it;
		}
	}



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


void CollisionHitManager::RegisterCollisionObject(EnCollisionType type, IGameObject* object, CollisionObject* collision)
{
	CollisionInfo info(type, object, collision);
	m_collisionInfoList.push_back(std::move(info));
}


void CollisionHitManager::UnregisterCollisionObject(IGameObject* object)
{
	for(auto it = m_collisionInfoList.begin(); it != m_collisionInfoList.end(); ++it)
	{
		if(it->m_object == object)
		{
			m_collisionInfoList.erase(it);
			break;
		}
	}
}