/**
 * DeliverySpace.h
 * 出来た料理を納品する
 */
#include "stdafx.h"
#include "DeliverySpace.h"
#include "collision/CollisionManager.h"


DeliverySpace::DeliverySpace()
{

}


DeliverySpace::~DeliverySpace()
{
	CollisionHitManager::Get().UnregisterCollisionObject(this);
}

bool DeliverySpace::Start()
{
	// 丸い判定を作る
	m_collisionObject.CreateSphere(m_transform.m_position, Quaternion::Identity, 5.0f/*m_radius*/);	// @todo for test
	UpdateTransform();

	// 当たり判定の処理をするため管理に登録する
	CollisionHitManager::Get().RegisterCollisionObject(enCollisionType_DeliverySpace, this, &m_collisionObject);

	// 初期化完了
	return true;
}


void DeliverySpace::Update()
{
	UpdateTransform();
}


void DeliverySpace::UpdateTransform()
{
	m_transform.UpdateTransform();
	m_collisionObject.SetPosition(m_transform.m_position);
	m_collisionObject.Update();
}