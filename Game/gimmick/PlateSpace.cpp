/**
 * PlateSpace.h
 * 皿が出てくる場所の判定を提供する
 */
#include "stdafx.h"
#include "PlateSpace.h"
#include "collision/GhostBody.h"
#include "collision/CollisionManager.h"


PlateSpace::PlateSpace()
{
}


PlateSpace::~PlateSpace()
{
	CollisionHitManager::Get().UnregisterCollisionObject(this);
}


bool PlateSpace::Start()
{
	// 丸い判定を作る
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, m_radius, enCollisionType_PlateSpace);
	UpdateTransform();

	// 初期化完了
	return true;
}


void PlateSpace::Update()
{
	UpdateTransform();
}


void PlateSpace::UpdateTransform()
{
	m_transform.UpdateTransform();
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
}