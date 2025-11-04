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
#include "gimmick/FoodSpace.h"
#include "gimmick/DeliverySpace.h"
#include "collision/CollisionManager.h"

#include "sound/SoundManager.h"

// @todo for test
#include "ui/UIBase.h"

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


	/** 食材箱の情報を取得 */
	struct FoodBoxExportInfo
	{
		std::string assetsPath;
		std::string cookedAssetsPath;
	};
	FoodBoxExportInfo ParseFoodBoxComponent(const nlohmann::json& j)
	{
		FoodBoxExportInfo info;
		info.assetsPath = j.at("assetPath").get<std::string>();
		info.cookedAssetsPath = j.at("cookedAssetPath").get<std::string>();
		return info;
	}

	// @todo for test
	static UICanvas* canvasTest = nullptr;
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
	for (int i = 0; i < 1;/* MAX_PLAYER_NUM;*/ ++i) {
		char name[] = "playerA";
		name[6] = 'A' + i;
		m_playerList[i] = NewGO<Player>(0, name);
		m_playerList[i]->m_transform.m_localScale = Vector3(2.0f,2.0f,1.0f);
		m_playerList[i]->m_transform.m_localPosition = Vector3(1.0f + static_cast<float>(i), 0.0f, 0.0f);
		m_playerList[i]->m_transform.UpdateTransform();
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
					cookingSpace->m_transform.UpdateTransform();
					cookingSpace->SetRadius(info.radius);
				}
				return true;
			}
			// まな板
			if (IsForwardMatchObjectName(name.c_str(), "Prop_CuttingPlate")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "cookingBoard");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			//包丁
			if (IsForwardMatchObjectName(name.c_str(), "Prop_Knife_04")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "knife");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			// 食材箱
			if (IsForwardMatchObjectName(name.c_str(), "Crate")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "foodBox");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, Vector3::One/*transform.scale*/, transform.rotation);	// TODO: Unityからの変換がおかしい？から、大きさは固定にする

				FoodSpace* foodSpace = nullptr;
				if (j.contains("InteractExportComponent")) {
					InteractExportInfo info = ParseInteractExportComponent(j["InteractExportComponent"]);
					
					foodSpace = NewGO<FoodSpace>(0, "foodSpace");
					foodSpace->m_transform.SetParent(&staticGimmick->m_transform);
					foodSpace->m_transform.m_localPosition = info.position;
					foodSpace->m_transform.UpdateTransform();
					foodSpace->SetRadius(info.radius);
				}
				if (j.contains("FoodBoxExportComponent")) {
					FoodBoxExportInfo info = ParseFoodBoxComponent(j["FoodBoxExportComponent"]);
					if (foodSpace) {
						foodSpace->SetAssetPath(info.assetsPath);
						foodSpace->SetCookedAssetsPath(info.cookedAssetsPath);
					}
				}
			}
			// 納品場
			if (IsForwardMatchObjectName(name.c_str(), "Prop_Fridge_04")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "delivery");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, Vector3::One/*transform.scale*/, transform.rotation);

				DeliverySpace* deliverySpace = nullptr;
				if (j.contains("InteractExportComponent")) {
					InteractExportInfo info = ParseInteractExportComponent(j["InteractExportComponent"]);

					deliverySpace = NewGO<DeliverySpace>(0, "deliverySpace");
					deliverySpace->m_transform.SetParent(&staticGimmick->m_transform);
					deliverySpace->m_transform.m_localPosition = info.position;
					deliverySpace->m_transform.UpdateTransform();
					deliverySpace->SetRadius(info.radius);
				}
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


	//// @todo for test
	//canvasTest = new UICanvas();
	//canvasTest->m_transform.m_localPosition = Vector3(500.0f, 0.0f, 0.0f);
	//// ゲージの背景
	//auto* uiGauge_back = canvasTest->CreateUI<UIGauge>();
	//uiGauge_back->Initialize("Assets/modelData/UI/Ber/ber.dds", 200.0f, 50.0f, Vector3(-100.0f, 50.0f, 0.0f), Vector3::One, Quaternion::Identity);
	//// ゲージ
	//auto* uiGauge_mid = canvasTest->CreateUI<UIGauge>();
	//uiGauge_mid->Initialize("Assets/modelData/UI/Ber/ber_mid.dds", 200.0f, 50.0f, Vector3(-100.0f, 50.0f, 0.0f), Vector3::One, Quaternion::Identity);
	//// ゲージの枠
	//auto* uiGauge_frame = canvasTest->CreateUI<UIGauge>();
	//uiGauge_frame->Initialize("Assets/modelData/UI/Ber/ber_waku.dds", 200.0f, 50.0f, Vector3(-100.0f, 50.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// @todo for test
	//m_uiGauge = uiGauge_mid; // 真ん中のゲージを覚えておく
	//m_uiGauge = uiGauge_mid;

	// BGM再生
	SoundManager::Get().PlayBGM(enSoundKind_Game);

	return true;
}


void GameScene::Update()
{
	// @todo for test
	CollisionHitManager::Get().Update();

	// @todo for test
	float m_pressTime = 0.0f; // 押している時間

	const float deltaTime = g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsPress(enButtonDown)) {
		m_pressTime += deltaTime; // 押している時間を足す
		//m_uiGauge->m_transform.m_localScale.x -= 0.1f;
	}
	else {
		m_pressTime = 0.0f;
	}

	//m_uiGauge->m_transform.m_localScale.x -= 0.1f;
	//uiGauge_mid->m_transform.localScale.x;

	/*if (g_pad[0]->IsPress(enButtonDown)) {
		canvasTest->m_transform.m_localScale.x -= 0.1f; 
	}*/
	//canvasTest->Update();
}


void GameScene::Render(RenderContext& rc)
{
	// @todo for test
	//canvasTest->Render(rc);
}


bool GameScene::RequestScene(uint32_t& id, float& waitTime)
{
	return false;
}
