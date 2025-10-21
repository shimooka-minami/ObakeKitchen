#include "stdafx.h"
#include "GameScene.h"

#include "GameCamera.h"
#include "BackGround.h"
#include "core/SceneLoader.h"

#include "actor/Player.h"
#include "actor/PlayerController.h"
#include "actor/Gimmick.h"
#include "actor/Plate.h"

#include "gimmick/CoockingSpace.h"
#include "collision/CollisionManager.h"

#include "sound/SoundManager.h"


namespace
{
	// シーンから読み込んだオブジェクトの名前が完全一致か
	bool IsMatchObjectName(const char* jsonNameA, const char* nameB)
	{
		if (strcmp(jsonNameA, nameB) == 0) {
			// 完全一致
			return true;
		}
		// 一致しない
		return false;
	}

	// 先頭から len 文字分が一致しているか判定する関数
	// オブジェクト同士1：1で名前が一致しているかを調べる
	bool IsForwardMatchObjectName(const char* jsonNameA, const char* nameB)
	{
		auto len = strlen(nameB);
		auto namelen = strlen(jsonNameA);
		if (len > namelen) {
			//名前が長い。不一致。
			return false;
		}
		if (strncmp(jsonNameA, nameB, len) == 0) {
			// 完全一致
			return true;
		}
		// 一致しない
		return false;
	}


	/**
	 * jsonから情報を取得する処理を下記に書く
	 */


	 /** 静的なオブジェクトの情報取得 */
	std::string ParseStaticMeshExportComponent(const nlohmann::json& j)
	{
		const std::string assetPath = j.at("assetPath").get<std::string>();
		return assetPath;
	}


	/** インタラクト情報の取得 */
	struct InteractExportInfo
	{
		Vector3 position;
		float radius;
	};
	InteractExportInfo ParseInteractExportComponent(const nlohmann::json& j)
	{
		InteractExportInfo info;
		info.position = json::ParseVector3(j.at("position"));
		info.radius = j.at("radius").get<float>();
		return info;
	}
}


GameScene::GameScene()
{

}


GameScene::~GameScene()
{

}


bool GameScene::Start()
{
	// プレイヤー
	for (int i = 0; i < MAX_PLAYER_NUM; ++i) {
		char name[] = "playerA";
		name[6] = 'A' + i;
		m_playerList[i] = NewGO<Player>(0, name);
		m_playerList[i]->m_transform.m_localScale = Vector3{2.0f,2.0f,1.0f};
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

			// Unityで配置しているオブジェクトの名前
			const std::string& name = j["name"];
			// 座標
			json::Transform transform = json::ParseTransformComponents(j["Transform"]);

			//地面
			if (IsForwardMatchObjectName(name.c_str(), "Env_Road_Free 1")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "ground");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
				return true;
			}


			// キッチン
			if (IsForwardMatchObjectName(name.c_str(), "Prop_KitchenCabinet_01")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "kitchen");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);

				if (j.contains("InteractExportComponent")) {
					InteractExportInfo info = ParseInteractExportComponent(j["InteractExportComponent"]);

					auto* cookingSpace = NewGO<CoockingSpace>(0, "coockingSpace");
					cookingSpace->m_transform.SetParent(&staticGimmick->m_transform);
					cookingSpace->m_transform.m_localPosition = info.position;
					cookingSpace->SetRadius(info.radius);
				}
				return true;
			}
			if (IsForwardMatchObjectName(name.c_str(), "Prop_CuttingPlate")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "cookingBoard");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			if (IsForwardMatchObjectName(name.c_str(), "Prop_Knife_04")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "knife");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			return true;
		});

	// TODO: 仮で投げるオブジェクトを置く
	auto* foodPlate = NewGO<FoodPlate>(0, "foodPlate");
	foodPlate->Initialize("Assets/modelData/food/tomato.tkm", "Assets/modelData/food/cut_tomato.tkm", Vector3(200.0f, 00.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Quaternion::Identity);

	// @todo for test
	// 判定管理生成
	CollisionHitManager::Create();
	// @todo for test
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	// BGM再生
	SoundManager::Get().PlayBGM(enSoundKind_Game);

	return true;
}


void GameScene::Update()
{
	// @todo for test
	CollisionHitManager::Get().Update();
}


void GameScene::Render(RenderContext& rc)
{

}


bool GameScene::RequestScene(uint32_t& id, float& waitTime)
{
	return false;
}
