/**
 * GhostBody.h
 * •¨—“I‚È•¨‘Ì‚Å‚Í‚È‚¢“–‚½‚è”»’è‚Ìˆ—ŒQ
 */
#include "stdafx.h"
#include "GhostBody.h"
#include "CollisionManager.h"


SphereGhostBody::SphereGhostBody()
{
}


SphereGhostBody::~SphereGhostBody()
{
	if (m_owner) {
		if (CollisionHitManager::IsAvailable()) {
			CollisionHitManager::Get().UnregisterCollisionObject(m_owner);
		}
	}
}


void SphereGhostBody::Update()
{
	auto sphereCollider = GetCollider();
	sphereCollider->SetPosition(m_position);
	sphereCollider->Update();
}


void SphereGhostBody::Create(IGameObject* owner, const Vector3& position, const float radius, const int collisionType)
{
	m_position = position;
	m_radisu = radius;
	m_collisionType = collisionType;

	m_collider = app::CreateSphereCollider(position, radius);

	// ”»’èˆ—‚É“o˜^
	if (CollisionHitManager::IsAvailable()) {
		CollisionHitManager::Get().RegisterCollisionObject(static_cast<EnCollisionType>(collisionType), owner, m_collider);
	}
}