/**
 * FoodSpace.h
 * 食材が出てくる場所の判定を提供する
 */
#include "stdafx.h"
#include "FoodSpace.h"
#include "collision/CollisionManager.h"


FoodSpace::FoodSpace()
{

}


FoodSpace::~FoodSpace()
{
	CollisionHitManager::Get().UnregisterCollisionObject(this);
}

bool FoodSpace::Start()
{
	// 丸い判定を作る
	m_collisionObject.CreateSphere(m_transform.m_position, Quaternion::Identity, 5.0f/*m_radius*/);	// @todo for test
	UpdateTransform();

	// 当たり判定の処理をするため管理に登録する
	CollisionHitManager::Get().RegisterCollisionObject(enCollisionType_FoodSpace, this, &m_collisionObject);

	// 初期化完了
	return true;
}


void FoodSpace::Update()
{
	UpdateTransform();
}


void FoodSpace::UpdateTransform()
{
	m_transform.UpdateTransform();
	m_collisionObject.SetPosition(m_transform.m_position);
	m_collisionObject.Update();
}