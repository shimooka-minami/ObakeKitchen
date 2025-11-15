/**
 * FoodSpace.h
 * 食材が出てくる場所の判定を提供する
 */
#include "stdafx.h"
#include "FoodSpace.h"
#include "collision/GhostBody.h"
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
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, m_radius, enCollisionType_FoodSpace);
	UpdateTransform();

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
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
}