/**
 * CoockingSpace.h
 * 料理する場所の判定を提供する
 */
#include "stdafx.h"
#include "CoockingSpace.h"
#include "collision/GhostBody.h"
#include "collision/CollisionManager.h"


CoockingSpace::CoockingSpace()
{
}


CoockingSpace::~CoockingSpace()
{
}


bool CoockingSpace::Start()
{
	// 丸い判定を作る
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, 10.0f/*m_radius*/, enCollisionType_CookingSpace);	// @todo for サイズはradiusに変更予定
	UpdateTransform();

	// 初期化完了
	return true;
}


void CoockingSpace::Update()
{
	UpdateTransform();
}


void CoockingSpace::UpdateTransform()
{
	m_transform.UpdateTransform();
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
}