/**
 * DeliverySpace.h
 * 出来た料理を納品する
 */
#include "stdafx.h"
#include "DeliverySpace.h"
#include "collision/GhostBody.h"
#include "collision/CollisionManager.h"


DeliverySpace::DeliverySpace()
{
}


DeliverySpace::~DeliverySpace()
{
}


bool DeliverySpace::Start()
{
	// 丸い判定を作る
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, m_radius, enCollisionType_DeliverySpace);
	UpdateTransform();

	// 初期化完了
	return true;
}


void DeliverySpace::Update()
{
	// 毎回初期化
	m_isNearPlayer = false;

	UpdateTransform();
}


void DeliverySpace::UpdateTransform()
{
	m_transform.UpdateTransform();
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
}