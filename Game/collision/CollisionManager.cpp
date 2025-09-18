#include "stdafx.h"
#include "CollisionManager.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"
#include "actor/Plate.h"


CollisionHitManager* CollisionHitManager::m_instance = nullptr;


void CollisionHitManager::Update()
{
	// @todo for test
	if (m_foodPlate->GetCollisionObject()->IsHit(*m_player->GetCharacterController())) {
		// ƒvƒŒƒCƒ„[‚ÆŽM‚ªÚG‚µ‚½‚Æ‚«‚Ìˆ—
		m_foodPlate->Throw(m_player->GetStateMachine()->GetDirection());
	}
}