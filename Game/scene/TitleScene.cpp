#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "sound/SoundManager.h"

// @todo for test
#include "ui/UIBase.h"
#include "actor/Player.h"
#include "core/SaveData.h"

namespace
{
	//const Vector3 MAX_PLAYER_POS = { -250.0f, 100.0f, 0.0f };
	constexpr float MAX_PLAYER_WIDTH = 300.0f;
	constexpr float MAX_PLAYER_HIGHT = 300.0f;

	//const Vector3 MAX_ICON_POS = { -250.0f, 100.0f, 0.0f };
	constexpr float MAX_ICON_WIDTH = 125.0f;
	constexpr float MAX_ICON_HIGHT = 75.0f;

	constexpr float MAX_NPC_ICON_WIDHT = 300.0f;
	constexpr float MAX_NPC_ICON_HIGHT = 55.0f;
}

namespace
{
	//struct TitleSpriteInformation
	//{
	//	std::string assetPath;
	//	Vector3 position;
	//	float width;
	//	float hight;
	//	//タイトルスプライト情報
	//	TitleSpriteInformation(const std::string& path, const Vector3& pos, const float w, const float h)
	//		: assetPath(path)
	//		, position(pos)
	//		, width(w)
	//		, hight(h)
	//	{
	//	}
	//};

	//static const TitleSpriteInformation titleSpriteInfoList[enTitleSpriteKind_Max] = {
	//	//TitleSpriteInformation("Assets/modelData/title/titleBack.dds", Vector3::Zero, MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT),
	//	//TitleSpriteInformation("Assets/modelData/title/titlelog.dds", Vector3(0.0f, 300.0f, 0.0f), 800.0f, 150.0f),
	//	//TitleSpriteInformation("Assets/modelData/title/push_a.dds", Vector3(0.0f, -150.0f, 0.0f), 300, 70),
	//};


	// プレイヤー人数選択の情報
	struct TitlePlayerSpriteInformation 
	{
		
		std::string playerPath;
		std::string upPath;
		//Vector3 iconPosition;
		Vector3 playerPosition;
		float width;
		float hight;
		//プレイヤースプライト情報
		TitlePlayerSpriteInformation(const std::string& player, const std::string& up, const Vector3& playerPos, const float w, const float h)
			: playerPath(player)
			, upPath(up)
			, playerPosition(playerPos)
			, width(w)
			, hight(h)
		{
		}
	};

	static const TitlePlayerSpriteInformation titlePlayerSpriteInfoList[] = {
		TitlePlayerSpriteInformation("Assets/modelData/menu/player/obake_player.dds","Assets/modelData/menu/player/obake_hansup.dds",Vector3(-250.0f, -100.0f, 0.0f),MAX_PLAYER_WIDTH, MAX_PLAYER_HIGHT),
		TitlePlayerSpriteInformation("Assets/modelData/menu/player/obake_player.dds","Assets/modelData/menu/player/obake_hansup.dds",Vector3(  50.0f, -100.0f, 0.0f),MAX_PLAYER_HIGHT, MAX_PLAYER_HIGHT),
		TitlePlayerSpriteInformation("Assets/modelData/menu/player/obake_player.dds","Assets/modelData/menu/player/obake_hansup.dds",Vector3( 350.0f, -100.0f, 0.0f),MAX_PLAYER_HIGHT, MAX_PLAYER_HIGHT),
		TitlePlayerSpriteInformation("Assets/modelData/menu/player/obake_player.dds","Assets/modelData/menu/player/obake_hansup.dds",Vector3( 650.0f, -100.0f, 0.0f),MAX_PLAYER_HIGHT, MAX_PLAYER_HIGHT),
	};


	// 1~4P & NPCアイコンの情報
	struct TitleIconSpriteInformation
	{
		std::string iconPath;
		std::string selectedIconPath;
		Vector3 iconPosition;
		float npcWidth;
		float npcHight;
		//アイコンスプライト情報
		TitleIconSpriteInformation(const std::string icon, const std::string selectedIcon, const Vector3& iconPos, const float npcW, const float npcH)
			: iconPath(icon)
			, selectedIconPath(selectedIcon)
			, iconPosition(iconPos)
			, npcWidth(npcW)
			, npcHight(npcH)
		{
		}
	};

	static const TitleIconSpriteInformation titleIconSpriteInfoList[] = {
	TitleIconSpriteInformation("Assets/modelData/UI/player/npc.dds","Assets/modelData/UI/player/1p.dds",Vector3(-250.0f, 100.0f, 0.0f),MAX_ICON_WIDTH, MAX_ICON_HIGHT),
	TitleIconSpriteInformation("Assets/modelData/UI/player/npc.dds","Assets/modelData/UI/player/2p.dds",Vector3(50.0f, 100.0f, 0.0f),MAX_ICON_WIDTH, MAX_ICON_HIGHT),
	TitleIconSpriteInformation("Assets/modelData/UI/player/npc.dds","Assets/modelData/UI/player/3p.dds",Vector3(350.0f, 100.0f, 0.0f),MAX_ICON_WIDTH, MAX_ICON_HIGHT),
	TitleIconSpriteInformation("Assets/modelData/UI/player/npc.dds","Assets/modelData/UI/player/4p.dds",Vector3( 650.0f, 100.0f, 0.0f),MAX_ICON_WIDTH, MAX_ICON_HIGHT),
	};
	

	// NPCの情報
	struct TitleNPCTypeSpriteInformation
	{

		std::string typePath;
		std::string selectedTypePath;
		Vector3 npcPosition;
		float width;
		float hight;
		//プレイヤースプライト情報
		TitleNPCTypeSpriteInformation(const std::string& type, const std::string& selectedType, const Vector3& npcPos, const float w, const float h)
			: typePath(type)
			, selectedTypePath(selectedType)
			, npcPosition(npcPos)
			, width(w)
			, hight(h)
		{
		}
	};

	static const TitleNPCTypeSpriteInformation titleNPCTypeSpriteInfoList[] = {
		TitleNPCTypeSpriteInformation("Assets/modelData/menu/player/obake_player.dds","Assets/modelData/menu/player/obake_hansup.dds",Vector3(-150.0f, -100.0f, 0.0f),MAX_PLAYER_WIDTH, MAX_PLAYER_HIGHT),
		TitleNPCTypeSpriteInformation("Assets/modelData/menu/player/obake_waru.dds","Assets/modelData/menu/player/waru_hansup.dds",Vector3(200.0f, -100.0f, 0.0f),MAX_PLAYER_HIGHT, MAX_PLAYER_HIGHT),
		TitleNPCTypeSpriteInformation("Assets/modelData/menu/player/obake_rondom.dds","Assets/modelData/menu/player/rondom_hansup.dds",Vector3(550.0f, -100.0f, 0.0f),MAX_PLAYER_HIGHT, MAX_PLAYER_HIGHT),
	};


	// 難易度アイコンの情報
	struct TitleTypeIconSpriteInformation
	{
		std::string npcIconPath;
		std::string selectedNPCIconPath;
		Vector3 npcIconPosition;
		float width;
		float hight;
		//アイコンスプライト情報
		TitleTypeIconSpriteInformation(const std::string npcIcon, const std::string selectedNPCIcon, const Vector3& npciconPos, const float w, const float h)
			: npcIconPath(npcIcon)
			, selectedNPCIconPath(selectedNPCIcon)
			, npcIconPosition(npciconPos)
			, width(w)
			, hight(h)
		{
		}
	};

	static const TitleTypeIconSpriteInformation titleNPCIconSpriteInfoList[] = {
	TitleTypeIconSpriteInformation("Assets/modelData/menu/ward/yasa.dds","Assets/modelData/UI/player/1p.dds",Vector3(-150.0f, 100.0f, 0.0f),MAX_NPC_ICON_WIDHT, MAX_NPC_ICON_HIGHT),
	TitleTypeIconSpriteInformation("Assets/modelData/menu/ward/waru.dds","Assets/modelData/UI/player/2p.dds",Vector3(200.0f, 100.0f, 0.0f),MAX_NPC_ICON_WIDHT, MAX_NPC_ICON_HIGHT),
	TitleTypeIconSpriteInformation("Assets/modelData/menu/ward/rondom.dds","Assets/modelData/UI/player/3p.dds",Vector3(550.0f, 100.0f, 0.0f),MAX_NPC_ICON_WIDHT, MAX_NPC_ICON_HIGHT),
	};

}




/**************************************************/


TitleStartMenu::TitleStartMenu()
{
}


TitleStartMenu::~TitleStartMenu()
{
}


bool TitleStartMenu::Start()
{
	m_uiCanvas = std::make_unique<UICanvas>();
	// スタートボタン表示生成
	auto* startButtonIcon = m_uiCanvas->CreateUI<UIIcon>();
	startButtonIcon->Initialize("Assets/modelData/title/push_a.dds", 300, 70, Vector3(0.0f, -150.0f, 0.0f), Vector3::One, Quaternion::Identity);
	{
		std::vector<Vector4> targetAlphaList = { Vector4(0.8f, 0.8f, 0.8f, 1.0f), Vector4(0.6f, 0.6f, 0.6f, 0.4f), Vector4(0.8f, 0.8f, 0.8f, 1.0f) };
		std::vector<float> timeList = { 0.8f,0.8f };
		auto* buttonAnimation = new ColorSpriteAnimation(startButtonIcon->GetSpriteRender(), true, timeList, targetAlphaList);
		startButtonIcon->AddSpriteAnimation(buttonAnimation);
		startButtonIcon->PlaySpriteAnimation();
	}

	// タイトル表示生成
	m_titleIcon = m_uiCanvas->CreateUI<UIIcon>();
	m_titleIcon->Initialize("Assets/modelData/title/kanban.dds", 500.0f, 657.0f, Vector3(-600.0f, 250.0f, 0.0f), Vector3::One, Quaternion::Identity);
	{
	/*	std::vector<Vector3> targetTanslateList = { Vector3::Zero, Vector3(0.0f, 600.0f, 0.0f) };
		std::vector<float> timeList = { 1.0f };
		auto* titleAnimation = new TranslateOffsetSpriteAnimation(m_titleIcon->GetSpriteRender(), false, timeList, targetTanslateList, &m_titleIcon->m_transform);
		m_titleIcon->AddSpriteAnimation(titleAnimation);*/

		std::vector<Vector3> targetTanslateList = { Vector3::Zero, Vector3(0.0f, 600.0f, 0.0f) };
		std::vector<float> timeList = { 1.0f };
		auto titleAnimation = std::make_unique<UIIcon>();
		//titleAnimation->SetSpriteAnimation
	}
	{
		std::vector<Vector4> targetAlphaList = { Vector4::White, Vector4(1.0f, 1.0f, 1.0f, 0.8f), Vector4(1.0f, 1.0f, 1.0f, 0.0f) };
		std::vector<float> timeList = { 0.7f, 0.1f };
		auto* titleAnimation = new ColorSpriteAnimation(m_titleIcon->GetSpriteRender(), false, timeList, targetAlphaList);
		m_titleIcon->AddSpriteAnimation(titleAnimation);
	}

	return true;
}


void TitleStartMenu::Update()
{
	if (!m_titleIcon->IsCompleted()) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_titleIcon->PlaySpriteAnimation();
		}
	}
	else {
		m_isChange = true;
	}

	m_uiCanvas->Update();
}


void TitleStartMenu::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}


bool TitleStartMenu::CanChange(int& request)
{
	if (m_isChange) {
		request = enTitleMenuType_Select;
		return true;
	}
	return false;
}




/**************************************************/


TitleSelectMenu::TitleSelectMenu()
{
}


TitleSelectMenu::~TitleSelectMenu()
{
}

bool TitleSelectMenu::Start()
{
	m_uiCanvas = std::make_unique<UICanvas>();
	// メニューの表示
	m_selectMenu = m_uiCanvas->CreateUI<UIIcon>();
	m_selectMenu->Initialize("Assets/modelData/menu/menu.dds", 800.0f, 1050.0f, Vector3(-450.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// アニメーション
	std::vector<Vector4> targetAlphaList = { Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
	std::vector<float> timeList = { 1.0f };
	auto* menuAnimation = new ColorSpriteAnimation(m_selectMenu->GetSpriteRender(), false, timeList, targetAlphaList);
	m_selectMenu->AddSpriteAnimation(menuAnimation);
	m_selectMenu->PlaySpriteAnimation();
	m_selectMenu->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));


	// ゲームスタート
	auto* ward = m_uiCanvas->CreateUI<UIIcon>();
	ward->Initialize("Assets/modelData/menu/gamestart.dds", 300.0f, 55.0f, Vector3(-450.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// アニメーション
	auto* wordAnimation = new ColorSpriteAnimation(ward->GetSpriteRender(), false, timeList, targetAlphaList);
	ward->AddSpriteAnimation(wordAnimation);
	ward->PlaySpriteAnimation();
	ward->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	// 操作方法
	ward = m_uiCanvas->CreateUI<UIIcon>();
	ward->Initialize("Assets/modelData/menu/sousahoho.dds", 300.0f, 55.0f, Vector3(-450.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// アニメーション
	wordAnimation = new ColorSpriteAnimation(ward->GetSpriteRender(), false, timeList, targetAlphaList);
	ward->AddSpriteAnimation(wordAnimation);
	ward->PlaySpriteAnimation();
	ward->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	// 設定
	ward = m_uiCanvas->CreateUI<UIIcon>();
	ward->Initialize("Assets/modelData/menu/settei.dds", 300.0f, 55.0f, Vector3(-450.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// アニメーション
	wordAnimation = new ColorSpriteAnimation(ward->GetSpriteRender(), false, timeList, targetAlphaList);
	ward->AddSpriteAnimation(wordAnimation);
	ward->PlaySpriteAnimation();
	ward->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	// おわり
	ward = m_uiCanvas->CreateUI<UIIcon>();
	ward->Initialize("Assets/modelData/menu/owaru.dds", 300.0f, 55.0f, Vector3(-450.0f, -200.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// アニメーション
	wordAnimation = new ColorSpriteAnimation(ward->GetSpriteRender(), false, timeList, targetAlphaList);
	ward->AddSpriteAnimation(wordAnimation);
	ward->PlaySpriteAnimation();
	ward->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	// 羽ペン
	m_penPosition = Vector3(-250.0f, 120.0f, 0.0f);
	m_hanePen = m_uiCanvas->CreateUI<UIIcon>();
	m_hanePen->Initialize("Assets/modelData/menu/hane.dds", 80.0f, 106.0f, m_penPosition, Vector3::One, Quaternion::Identity);
	// アニメーション
	menuAnimation = new ColorSpriteAnimation(m_hanePen->GetSpriteRender(), false, timeList, targetAlphaList);
	m_hanePen->AddSpriteAnimation(menuAnimation);
	m_hanePen->PlaySpriteAnimation();
	m_hanePen->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	// 線
	m_senPosition = Vector3(-450.0f, 65.0f, 0.0f);
	m_sen = m_uiCanvas->CreateUI<UIIcon>();
	m_sen->Initialize("Assets/modelData/menu/sen.dds", 250.0f, 11.0f, m_senPosition, Vector3::One, Quaternion::Identity);
	// アニメーション
	menuAnimation = new ColorSpriteAnimation(m_sen->GetSpriteRender(), false, timeList, targetAlphaList);
	m_sen->AddSpriteAnimation(menuAnimation);
	m_sen->PlaySpriteAnimation();
	m_sen->GetSpriteRender()->SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

	return true;
}


void TitleSelectMenu::Update()
{
	// メニュー選択
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		--m_currentSelectIndex;
		// 最小値
		if (m_currentSelectIndex < enSelectMenuType_GameStart)
		{
			m_currentSelectIndex = enSelectMenuType_GameStart; //範囲外にならないように調整
		}
	}
	else if (g_pad[0]->IsTrigger(enButtonDown))
	{
		++m_currentSelectIndex;
		// 最大値
		if (m_currentSelectIndex >= enSelectMenuType_Num)
		{
			m_currentSelectIndex = enSelectMenuType_Num - 1; //範囲外にならないように調整
		}
	}

	// 下線の座標を変える
	m_sen->m_transform.m_localPosition = m_senPosition + (Vector3(0.0f, -100.f, 0.0f) * m_currentSelectIndex);
	// 羽ペンの座標を変える
	m_hanePen->m_transform.m_localPosition = m_penPosition + (Vector3(0.0f, -100.0f, 0.0f) * m_currentSelectIndex);

	// 下線の大きさを文字の大きさに変える
	float senScaleList[] = { 1.4f, 1.1f, 0.6f, 0.8f };
	m_sen->m_transform.m_localScale = Vector3(senScaleList[m_currentSelectIndex], 1.0f, 1.0f);


	if (!m_isPlayAnimation) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_selectMenu->PlaySpriteAnimation();
			m_isPlayAnimation = true;
		}
	}
	else {
		if (m_selectMenu->IsCompleted()) {
			m_isChange = true;
		}
	}

	m_uiCanvas->Update();
}


void TitleSelectMenu::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}


bool TitleSelectMenu::CanChange(int& request)
{
	if (m_isChange)
	{
		switch (m_currentSelectIndex)
		{
		case enSelectMenuType_GameStart:
		{
			// TODO: プレイ人数選択にしたい
			//TitleScene::SetStartGame(true);
			request = enTitleMenuType_Play;
			return true;
		}
		case enSelectMenuType_Operation:
		{
			request = enTitleMenuType_Cotrol;
			return true;
		}
		case enSelectMenuType_Setting:
		{
			// 設定画面は未実装
			request = enTitleMenuType_Setting;
			return true;
		}
		case enSelectMenuType_End:
		{
			// ゲーム終了
			exit(0);
			break;
		}
		default:
		{
			K2_ASSERT(false, "未実装");
			break;
		}
		}
	}

	return false;
}




/**************************************************/


TitlePlayerSelectMenu::TitlePlayerSelectMenu()
{

}

TitlePlayerSelectMenu::~TitlePlayerSelectMenu()
{

}

bool TitlePlayerSelectMenu::Start()
{
	m_uiCanvas = std::make_unique<UICanvas>();

	// プレイヤー人数
	auto* playerBack = m_uiCanvas->CreateUI<UIIcon>();
	playerBack->Initialize("Assets/modelData/menu/player_num.dds", 1700.0f, 1050.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

	//
	for (int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		// おばけ
		m_playerObake[i] = m_uiCanvas->CreateUI<UIIcon>();
		m_playerObake[i]->Initialize(titlePlayerSpriteInfoList[i].playerPath.c_str(), titlePlayerSpriteInfoList[i].width, titlePlayerSpriteInfoList[i].hight, titlePlayerSpriteInfoList[i].playerPosition,Vector3::One,Quaternion::Identity);
		// プレイヤーナンバー
		m_playerNumber[i] = m_uiCanvas->CreateUI<UIIcon>();
		m_playerNumber[i]->Initialize(titleIconSpriteInfoList[i].iconPath.c_str(), titleIconSpriteInfoList[i].npcWidth, titleIconSpriteInfoList[i].npcHight, titleIconSpriteInfoList[i].iconPosition,Vector3::One,Quaternion::Identity);
	}


	//// おばけ
	//m_playerObake[0] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerObake[0]->Initialize("Assets/modelData/menu/obake_hansup.dds", 300.0f, 300.0f, Vector3(-250.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	//// プレイヤーナンバー
	//m_playerNumber[0] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerNumber[0]->Initialize("Assets/modelData/UI/player/1P.dds", 125.0f, 75.0f, Vector3(-250.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	//// おばけ
	//m_playerObake[1] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerObake[1]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3(50.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	//// プレイヤーナンバー
	//m_playerNumber[1] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerNumber[1]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f, Vector3(50.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	//// おばけ
	//m_playerObake[2] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerObake[2]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3(350.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	//// プレイヤーナンバー
	//m_playerNumber[2] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerNumber[2]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f, Vector3(350.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	//// おばけ
	//m_playerObake[3] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerObake[3]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3(650.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	//// プレイヤーナンバー
	//m_playerNumber[3] = m_uiCanvas->CreateUI<UIIcon>();
	//m_playerNumber[3]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f, Vector3(650.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// もどる
	auto* m_backObake = m_uiCanvas->CreateUI<UIIcon>();
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f, Vector3(-665.0f, -300.0f, 0.0f), Vector3::One, Quaternion::Identity);

	return true;
}

void TitlePlayerSelectMenu::Update()
{
	for (int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		if (g_pad[i]->IsTrigger(enButtonUp))
		{
			m_isPlayerConected[i] = true;
		}
		if (g_pad[i]->IsTrigger(enButtonDown))
		{
			m_isPlayerConected[i] = false;
		}
		SaveData::GetInstance()->SetContolerConected(i, m_isPlayerConected[i]);
	}

	for (int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		if (m_isPlayerConected[i])
		{
			// おばけの手が上がる
			m_playerObake[i]->Initialize(titlePlayerSpriteInfoList[i].upPath.c_str(), titlePlayerSpriteInfoList[i].width, titlePlayerSpriteInfoList[i].hight, titlePlayerSpriteInfoList[i].playerPosition, Vector3::One, Quaternion::Identity);
			// プレイヤー人数が増える
			m_playerNumber[i]->Initialize(titleIconSpriteInfoList[i].selectedIconPath.c_str(), titleIconSpriteInfoList[i].npcWidth, titleIconSpriteInfoList[i].npcHight, titleIconSpriteInfoList[i].iconPosition, Vector3::One, Quaternion::Identity);
		}
		else {
			// おばけの手がさがる
			m_playerObake[i]->Initialize(titlePlayerSpriteInfoList[i].playerPath.c_str(), titlePlayerSpriteInfoList[i].width, titlePlayerSpriteInfoList[i].hight, titlePlayerSpriteInfoList[i].playerPosition, Vector3::One, Quaternion::Identity);
			// プレイヤー人数が減る
			m_playerNumber[i]->Initialize(titleIconSpriteInfoList[i].iconPath.c_str(), titleIconSpriteInfoList[i].npcWidth, titleIconSpriteInfoList[i].npcHight, titleIconSpriteInfoList[i].iconPosition, Vector3::One, Quaternion::Identity);
		}
	}

	// インゲームに行く
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		TitleScene::SetStartGame(true);
	}

	// 戻る
	if (!m_isBack)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_isBack = true;
		}
	}

	m_uiCanvas->Update();
}

void TitlePlayerSelectMenu::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

bool TitlePlayerSelectMenu::CanChange(int& request)
{
	if (m_isBack) {
		request = enTitleMenuType_Select;
		return true;
	}
	return false;
}





/**************************************************/


TitleControlGuide::TitleControlGuide()
{

}

TitleControlGuide::~TitleControlGuide()
{

}

bool TitleControlGuide::Start()
{
	m_uiCanvas = std::make_unique<UICanvas>();
	// 操作方法
	auto* controlGuide = m_uiCanvas->CreateUI<UIIcon>();
	controlGuide->Initialize("Assets/modelData/menu/contlloer.dds", 1700.0f, 1050.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
	// もどる
	auto* m_backObake = m_uiCanvas->CreateUI<UIIcon>();
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f, Vector3(-665.0f, -300.0f, 0.0f), Vector3::One, Quaternion::Identity);

	return true;
}

void TitleControlGuide::Update()
{
	if (!m_isBack)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_isBack = true;
		}
	}
	m_uiCanvas->Update();
}

void TitleControlGuide::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

bool TitleControlGuide::CanChange(int& request)
{
	if (m_isBack) {
		request = enTitleMenuType_Select;
		return true;
	}
	return false;
}




/**************************************************/


TitleSetting::TitleSetting()
{
}

TitleSetting::~TitleSetting()
{
}

bool TitleSetting::Start()
{
	m_uiCanvas = std::make_unique<UICanvas>();
	// npcのタイプ設定
	auto* controlGuide = m_uiCanvas->CreateUI<UIIcon>();
	controlGuide->Initialize("Assets/modelData/menu/seikaku.dds", 1700.0f, 1050.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);

	//npc
	for (int i = 0; i < NPC_TYPE_NUM; i++)
	{
		// おばけ
		m_npcTypeObake[i] = m_uiCanvas->CreateUI<UIIcon>();
		m_npcTypeObake[i]->Initialize(titleNPCTypeSpriteInfoList[i].typePath.c_str(), titleNPCTypeSpriteInfoList[i].width, titleNPCTypeSpriteInfoList[i].hight, titleNPCTypeSpriteInfoList[i].npcPosition, Vector3::One, Quaternion::Identity);
		// 性格
		m_npcTypeIcon[i] = m_uiCanvas->CreateUI<UIIcon>();
		m_npcTypeIcon[i]->Initialize(titleNPCIconSpriteInfoList[i].npcIconPath.c_str(), titleNPCIconSpriteInfoList[i].width, titleNPCIconSpriteInfoList[i].hight, titleNPCIconSpriteInfoList[i].npcIconPosition, Vector3::One, Quaternion::Identity);
	}

	// もどる
	auto* m_backObake = m_uiCanvas->CreateUI<UIIcon>();
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f, Vector3(-665.0f, -300.0f, 0.0f), Vector3::One, Quaternion::Identity);

	return true;
}

void TitleSetting::Update()
{
	int npcType = m_npcTypeIndex;

	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		m_isNPCConected[m_npcTypeIndex] = false;
		npcType++;
		if (npcType >= NPC_TYPE_NUM) {
			npcType = NPC_TYPE_NUM - 1;
		}
		m_isNPCConected[npcType] = true;
	}
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_isNPCConected[m_npcTypeIndex] = false;
		npcType--;
		if (npcType <= 0) {
			npcType = 0;
		}
		m_isNPCConected[npcType] = true;
	}
	m_npcTypeIndex = npcType;
	//SaveData::GetInstance()->SetContolerConected(0, m_isNPCConected[0]);
	

	for (int i = 0; i < NPC_TYPE_NUM; i++)
	{
		if (m_isNPCConected[i])
		{
			// おばけの手が上がる
			m_npcTypeObake[i]->Initialize(titleNPCTypeSpriteInfoList[i].selectedTypePath.c_str(), titleNPCTypeSpriteInfoList[i].width, titleNPCTypeSpriteInfoList[i].hight, titleNPCTypeSpriteInfoList[i].npcPosition, Vector3::One, Quaternion::Identity);
		}
		else {
			// おばけの手がさがる
			m_npcTypeObake[i]->Initialize(titleNPCTypeSpriteInfoList[i].typePath.c_str(), titleNPCTypeSpriteInfoList[i].width, titleNPCTypeSpriteInfoList[i].hight, titleNPCTypeSpriteInfoList[i].npcPosition, Vector3::One, Quaternion::Identity);
		}
	}

	//// メニュー選択
	//if (g_pad[0]->IsTrigger(enButtonUp))
	//{
	//	--m_npcTypeIndex;
	//	// 最小値
	//	if (m_npcTypeIndex < enNPCType_kind)
	//	{
	//		m_npcTypeIndex = enNPCType_kind; //範囲外にならないように調整
	//	}
	//}
	//else if (g_pad[0]->IsTrigger(enButtonDown))
	//{
	//	++m_npcTypeIndex;
	//	// 最大値
	//	if (m_npcTypeIndex >= enNPCType_Max)
	//	{
	//		m_npcTypeIndex = enNPCType_Max - 1; //範囲外にならないように調整
	//	}
	//}

	if (!m_isBack)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_isBack = true;
		}
	}
	m_uiCanvas->Update();
}

void TitleSetting::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

bool TitleSetting::CanChange(int& request)
{

	if (m_isBack) {
		request = enTitleMenuType_Select;
		return true;
	}
	
	return false;
}




/**************************************************/


bool TitleScene::sIsStartGame = false;


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
	SoundManager::Get().StopBGM();
	DeleteGO(m_player);
}


bool TitleScene::Start()
{
	//for (int i = 0; i < enTitleSpriteKind_Max; i++) {
	// const auto& info = titleSpriteInfoList[i];
	// m_spriteRender[i].Init(info.assetPath.c_str(), info.width, info.hight);
	// m_spriteRender[i].SetPosition(info.position);
	//}

	m_player = NewGO<Player>(0, "player");
	m_player->m_transform.m_localPosition.Set(100.0f, 0.0f, 0.0f);
	m_player->m_transform.m_localRotation.SetRotationDegY(200.0f);
	m_player->m_transform.m_localScale.Set(1.5f, 1.5f, 1.5f);

	ChangeTitleMenu();

	// タイトル画面の3D.tkm
	m_titleBack = std::make_unique<ModelRender>();
	m_titleBack->Init("Assets/modelData/Ground/title_back.tkm");
	m_titleBack->SetPosition(Vector3(0.0f, 0.0f, 30.0f));
	m_titleBack->SetScale(Vector3::One * 0.4f);
	m_titleBack->Update();

	// 看板を仮表示
	//m_titleRender = std::make_unique<SpriteRender>();
	//m_titleRender->Init("Assets/modelData/title/kanban.dds",500.0f,657.0f);
	//m_titleRender->SetPosition(Vector3(-600.0f, 250.0f, 0.0f));
	//m_titleRender->SetScale(Vector3::One);
	//m_titleRender->Update();


	SoundManager::Get().PlayBGM(enSoundKind_Title);

	// ライト調整
	g_sceneLight->SetDirectionLight(0, Vector3(1.0f, -1.0f, 0.0f), Vector3(0.8f, 0.8f, 0.8f));
	g_sceneLight->SetAmbinet(Vector3(0.2f, 0.2f, 0.2f));

	// カメラの初期化
	g_camera3D->SetTarget(Vector3(0.0f, 50.0f, 0.0f));
	g_camera3D->SetPosition(Vector3(0.0f, 130.0f, -190.0f));
	g_camera3D->Update();

	return true;
}


void TitleScene::Update()
{
	if (sIsStartGame)
	{
		if (!m_isRequestNext) {
			SoundManager::Get().PlaySE(enSoundKind_Button);
			m_isRequestNext = true;
		}
		sIsStartGame = false;
	}
	else
	{
		if (m_currentMenu < enTitleMenuType_Num) {
			int request;
			if (m_titleMenu->CanChange(request)) {
				// 次のメニューへ
				m_currentMenu = request;
				ChangeTitleMenu();
			}
		}
		m_titleMenu->Update();
	}
}


void TitleScene::Render(RenderContext& rc)
{
	//for (int i = 0; i < enTitleSpriteKind_Max; i++) {
	// m_spriteRender[i].Draw(rc);
	//}

	// タイトル画面
	m_titleBack->Draw(rc);
	// 看板の仮表示
	//m_titleRender->Draw(rc);
	// メニュー表示
	m_titleMenu->Render(rc);
}


bool TitleScene::RequestScene(uint32_t& id, float& waitTime)
{
	if (m_isRequestNext) {
		id = GameScene::ID();
		waitTime = 3.0f;
		return true;
	}
	return false;
}


void TitleScene::ChangeTitleMenu()
{
	ITtitleMenu* titleMenu = nullptr;
	switch (m_currentMenu)
	{
	case enTitleMenuType_Start:
	{
		titleMenu = new TitleStartMenu();
		break;
	}
	case enTitleMenuType_Select:
	{
		titleMenu = new TitleSelectMenu();
		break;
	}
	case enTitleMenuType_Play:
	{
		titleMenu = new TitlePlayerSelectMenu;
		break;
	}
	case enTitleMenuType_Cotrol:
	{
		titleMenu = new TitleControlGuide();
		break;
	}
	case enTitleMenuType_Setting:
	{
		titleMenu = new TitleSetting();
		break;
	}
	default:
	{
		K2_ASSERT(false, "Menuを追加してください");
	}
	}
	titleMenu->Start();
	m_titleMenu = std::unique_ptr<ITtitleMenu>(titleMenu);
}