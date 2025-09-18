/**
 * Actor.h
 * 見た目が存在するゲームオブジェクトの基底クラス
 */
#include "stdafx.h"
#include "ActorStatus.h"
#include "core/ParameterManager.h"


PlayerStatus::PlayerStatus()
{
	// 外部ファイルを読み込み
	ParameterManager::Get().LoadParameter<MasterPlayerStatusParameter>("Assets/parameter/PlayerStatus.json", [](const nlohmann::json& j, MasterPlayerStatusParameter& parameter)
		{
			parameter.speed = j["speed"].get<float>();
			parameter.dashSpeed = j["dash"].get<float>();
			parameter.radius = j["radius"].get<float>();
			parameter.height = j["height"].get<float>();
		});
}


PlayerStatus::~PlayerStatus()
{
	// 使用が終わったので解放
	ParameterManager::Get().UnloadParameter<MasterPlayerStatusParameter>();
}


void PlayerStatus::Setup()
{
	// 読み込んだパラメーター取得
	const auto* parameter = ParameterManager::Get().GetParameter<MasterPlayerStatusParameter>();
	m_speed = parameter->speed;
	m_dashSpeed = parameter->dashSpeed;
	m_radius = parameter->radius;
	m_height = parameter->height;
}




/**************************************************/




FoodStatus::FoodStatus()
{
	// 外部ファイルを読み込み
	ParameterManager::Get().LoadParameter<MasterFoodStatusParameter>("Assets/parameter/FoodStatus.json", [](const nlohmann::json& j, MasterFoodStatusParameter& parameter)
		{
			parameter.radius = j["radius"].get<float>();
			parameter.height = j["height"].get<float>();
			parameter.addForcePower = j["addForcePower"].get<float>();
		});
}


FoodStatus::~FoodStatus()
{
	// 使用が終わったので解放
	ParameterManager::Get().UnloadParameter<MasterFoodStatusParameter>();
}


void FoodStatus::Setup()
{
	// 読み込んだパラメーター取得
	const auto* parameter = ParameterManager::Get().GetParameter<MasterFoodStatusParameter>();
	m_radius = parameter->radius;
	m_height = parameter->height;
	m_addForcePower = parameter->addForcePower;
}