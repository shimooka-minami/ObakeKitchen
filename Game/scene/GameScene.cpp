#include "stdafx.h"

#include "GameScene.h"
#include "ResultScene.h"

#include "GameCamera.h"
#include "BackGround.h"

#include "core/SceneLoader.h"
#include "core/TimeKeeper.h"

#include "actor/Player.h"
#include "actor/PlayerController.h"
#include "actor/Gimmick.h"
#include "actor/Plate.h"

#include "gimmick/CoockingSpace.h"
#include "gimmick/FoodSpace.h"
#include "gimmick/DeliverySpace.h"
#include "collision/CollisionManager.h"

#include "score/Score.h"

#include "sound/SoundManager.h"

// @todo for test
#include "ui/UIBase.h"
#include "ui/UIScore.h"
#include "ui/UITimer.h"
#include "ui/UIPlayerNumber.h"

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
	DeleteGO(m_uiScore);
	DeleteGO(m_uiTimer);

	for (int i = 0; i < MAX_PLAYER_NUM; ++i) {
		DeleteGO(m_playerList[i]);
		DeleteGO(m_playerControllerList[i]);
		DeleteGO(m_uiPlayerNumber[i]);
	}
}


bool GameScene::Start()
{
	// プレイヤー
	for (int i = 0; i <  MAX_PLAYER_NUM; ++i) {
		char name[] = "playerA";
		name[6] = 'A' + i;
		m_playerList[i] = NewGO<Player>(0, name);
		m_playerList[i]->m_transform.m_localScale = Vector3(2.0f,2.0f,2.0f);
		m_playerList[i]->m_transform.m_localPosition = Vector3(1.0f + static_cast<float>(i), 0.0f, 0.0f);
		m_playerList[i]->m_transform.UpdateTransform();
		// プレイヤーコントローラー
		m_playerControllerList[i] = NewGO<PlayerController>(0, "playerController");
		// TODO: 仮で対象を設定。
		m_playerControllerList[i]->SetTarget(m_playerList[i], i);

		m_uiPlayerNumber[i] = NewGO<UIPlayerNumber>(0, "uiPlayerNumber");
		m_uiPlayerNumber[i]->Initialize(i + 1);	// iは0からなので+1して数にする(iはindexなので0から)
	}

	

	// カメラ
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	// 
	LoadScene("Assets/scene/SceneExport.json", [](const nlohmann::json& j)
		{
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
			// 食材のアイコン(トマト)
			if (IsForwardMatchObjectName(name.c_str(), "tomato_top")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "tomato_top");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			// 食材のアイコン(レタス)
			if (IsForwardMatchObjectName(name.c_str(), "retasu_top")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "retasu_top");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			// 食材のアイコン(おにく)
			if (IsForwardMatchObjectName(name.c_str(), "meet_top")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "meet_top");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position, transform.scale, transform.rotation);
			}
			// 食材箱
			if (IsForwardMatchObjectName(name.c_str(), "BoxReady")) {
				auto* staticGimmick = NewGO<StaticGimmick>(0, "foodBox");
				const std::string assetPath = ParseStaticMeshExportComponent(j["StaticMeshExportComponent"]);
				staticGimmick->Initialize(assetPath.c_str(), transform.position,/* Vector3::One*/transform.scale, transform.rotation);	// TODO: Unityからの変換がおかしい？から、大きさは固定にする

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

	// 判定管理生成
	CollisionHitManager::Create();

	// タイムキーパーの生成
	m_timeKeeper = std::make_unique<TimeKeeper>();
	// @todo for test
	// 仮で制限時間を入れる
	m_timeKeeper->SetLimitTime(90);

	// スコア管理の生成
	Score::CreateInstance();

	// BGM再生
	SoundManager::Get().PlayBGM(enSoundKind_Game);

	// @todo for test
	m_uiScore = NewGO<UIScore>(0, "uiScore");
	
	// 制限時間のUI
	m_uiTimer = NewGO<UITimer>(0, "uiTimer");

	return true;
}


void GameScene::Update()
{
	// @todo for test
	CollisionHitManager::Get().Update();

	// @todo for test
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		Score::GetInstance()->AddScore(100);
	}


	m_uiScore->SetScore(Score::GetInstance()->GetScore());

	// 制限時間
	m_timeKeeper->Update();							// 時間進める		// 29.0f;
	m_uiTimer->SetTimer(m_timeKeeper->GetRemainingTime());	// 時間設定			// 30.0f

	
	// 制限時間をこえたら次のシーン
	if(m_timeKeeper->IsTimeOver())
	{
		m_isNextScene = true;
	}
	

	// UIの座標を更新
	for (int i = 0; i < MAX_PLAYER_NUM; ++i) {
		m_uiPlayerNumber[i]->SetPosition(m_playerList[i]->m_transform.m_position);
	}
}


void GameScene::Render(RenderContext& rc)
{
}


bool GameScene::RequestScene(uint32_t& id, float& waitTime)
{
	if (m_isNextScene)
	{
		id = ResultScene::ID();
		return true;
	}
	return false;
}
