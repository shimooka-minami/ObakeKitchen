#include "stdafx.h"
#include "Game.h"

#include "actor/Player.h"
#include "actor/PlayerController.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "core/SceneLoader.h"

#include "actor/Gimmick.h"
#include "actor/Plate.h"

// @todo for test
#include "collision/CollisionManager.h"


//Game::Game()
//{
//
//}
//
//Game::~Game()
//{
//	DeleteGO(m_player);
//}

bool Game::Start()
{
	// プレイヤー
	for (int i = 0; i < MAX_PLAYER_NUM; ++i) {
		char name[] = "playerA";
		name[6] = 'A' + i;
		m_playerList[i] = NewGO<Player>(0, name);
	}

	// プレイヤーコントローラー
	m_playerContoller = NewGO<PlayerController>(0, "playerController");
	// TODO: 仮で対象を設定。
	m_playerContoller->SetTarget(m_playerList[0]);

	// カメラ
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	// 地面
	//m_backGround = NewGO<BackGround>(0, "backGround");

	// 
	LoadScene("Assets/scene/SceneExport.json", [](const nlohmann::json& j) 
		{
			// TODO: あとからこんな感じにする
			//auto* object = NewGO<Gimmick>(0);
			//object->SetModelName(j["modelName"]);
			//object->SetPosition(j["position"]);

			// TODO: 仮でオブジェクトを置けるかテスト
			auto* staticGimmick = NewGO<StaticGimmick>(0, "backGround");
			Vector3 pos;
			Quaternion rot;
			Vector3 scale;
			std::tie(pos, rot, scale) = ParseTransformComponents(j["Transform"]);

			// StaticMeshExportComponentのパーサをつくって 
			// ParseTransformComponentsを参考に
			// 場所は任せる
			const auto& staticMeshComponent = j["StaticMeshExportComponent"];
			const std::string assetPath = staticMeshComponent.at("assetPath").get<std::string > ();

			staticGimmick->Initialize(assetPath.c_str(), pos, scale, rot);

			return true;
		});

	// TODO: 仮で投げるオブジェクトを置く
	auto* foodPlate = NewGO<FoodPlate>(0, "foodPlate");
	foodPlate->Initialize("Assets/modelData/Ground/ground.tkm", Vector3(200.0f, 20.0f, 0.0f), Vector3(0.3f, 0.5f, 0.3f), Quaternion::Identity);

	// @todo for test
	// 判定管理生成
	CollisionHitManager::Create();
	CollisionHitManager::Get().SetPlayer(m_playerList[0]);
	CollisionHitManager::Get().SetFoodPlate(foodPlate);
	// @todo for test
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Game::Update()
{
	// @todo for test
	CollisionHitManager::Get().Update();
}

void Game::Render(RenderContext& rc)
{
	
}