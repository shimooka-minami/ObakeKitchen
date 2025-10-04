/**
 * CoockingSpace.h
 * 料理する場所の判定を提供する
 */
#include "stdafx.h"
#include "CoockingSpace.h"
#include "collision/CollisionManager.h"


CoockingSpace::CoockingSpace()
{

}


CoockingSpace::~CoockingSpace()
{
	CollisionHitManager::Get().UnregisterCollisionObject(this);
}

bool CoockingSpace::Start()
{
	// 丸い判定を作る
	// あとで座標更新されるので、一旦座標は0
	m_collisionObject.CreateSphere(Vector3::Zero, Quaternion::Identity, m_radius);

	// 当たり判定の処理をするため管理に登録する
	CollisionHitManager::Get().RegisterCollisionObject(enCollisionType_CookingSpace, this, &m_collisionObject);

	// 初期化完了
	return true;
}


void CoockingSpace::Update()
{
	m_transform.UpdateTransform();
	m_collisionObject.SetPosition(m_transform.m_position);
	m_collisionObject.Update();
}