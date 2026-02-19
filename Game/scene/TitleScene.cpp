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
	auto* startButtonIcon = m_uiCanvas->CreateUI<UIIcon>(0);
	startButtonIcon->Initialize("Assets/modelData/title/push_a.dds", 300, 70);
	startButtonIcon->m_transform.m_localPosition = Vector3(0.0f, -150.0f, 0.0f);
	{
		auto colorAnimaiton = std::make_unique<UIColorAnimation>();
		colorAnimaiton->SetParameter(Vector4(0.6f, 0.6f, 0.6f, 0.4f), Vector4(0.8f, 0.8f, 0.8f, 1.0f), 1.5f, EasingType::Linear, LoopMode::PingPong);
		startButtonIcon->AddAnimation(Hash32("startButtonColorAnimation"), std::move(colorAnimaiton));
		startButtonIcon->PlayAnimation();
	}

	// タイトル表示生成
	m_titleIcon = m_uiCanvas->CreateUI<UIIcon>(1);
	m_titleIcon->Initialize("Assets/modelData/title/kanban.dds", 500.0f, 657.0f);
	m_titleIcon->m_transform.m_localPosition = Vector3(-600.0f, 250.0f, 0.0f);
	{
		auto translateAnimation = std::make_unique<UITranslateAniamtion>();
		translateAnimation->SetParameter(Vector3(-600.0f,250.0f,0.0f), Vector3(-600.0f, 1040.0f, 0.0f), 1.5f, EasingType::Linear, LoopMode::Once);
		translateAnimation->Stop();
		m_titleIcon->AddAnimation(Hash32("titleTranslateAnimation"), std::move(translateAnimation));
	}
	{
		//  auto colorAnimation = std::make_unique<UIColorAnimation>();
		//  colorAnimation->SetParameter(Vector4::White, Vector4(1.0f, 1.0f, 1.0f, 0.8f), 0.7f, EasingType::Linear, LoopMode::Once);
		//  colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.8f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 0.1f, EasingType::Linear, LoopMode::Once);
		//  m_titleIcon->AddAnimation(Hash32("titleColorAnimation"), std::move(colorAnimation));
		//m_titleIcon->PlayAnimation();
	}

	return true;
}


void TitleStartMenu::Update()
{
	if (m_isChange) {
		m_uiCanvas->Update();
		return;
	}

	if (!m_isPressed) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_isPressed = true;
			m_titleIcon->PlayAnimation();
		}
	}
	else {
		if (m_titleIcon->IsComplted()) {
			m_isChange = true;
		}
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

	//// メニューの表示
	m_selectMenu = m_uiCanvas->CreateUI<UIIcon>(0);
	m_selectMenu->Initialize("Assets/modelData/menu/menu.dds", 800.0f, 1050.0f);
	m_selectMenu->m_transform.m_localPosition = Vector3(-450.0f, 0.0f, 0.0f);
	m_selectMenu->m_color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		colorAnimation->Stop();
		m_selectMenu->AddAnimation(Hash32("menuColorAnimation"), std::move(colorAnimation));
		m_selectMenu->PlayAnimation();
		//m_selectMenu->m_uiAnimationList.clear();
	}
	

	//// ゲームスタート
	m_startWard = m_uiCanvas->CreateUI<UIIcon>(1);
	m_startWard->Initialize("Assets/modelData/menu/gamestart.dds", 300.0f, 55.0f);
	m_startWard->m_transform.m_localPosition = Vector3(-450.0f, 100.0f, 0.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		m_startWard->AddAnimation(Hash32("startWardColorAnimation"), std::move(colorAnimation));
		m_startWard->PlayAnimation();
	}
	
	//// 操作方法
	m_guideWard = m_uiCanvas->CreateUI<UIIcon>(2);
	m_guideWard->Initialize("Assets/modelData/menu/sousahoho.dds", 300.0f, 55.0f);
	m_guideWard->m_transform.m_localPosition = Vector3(-450.0f, 0.0f, 0.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		m_guideWard->AddAnimation(Hash32("guideWardColorAnimation"), std::move(colorAnimation));
		m_guideWard->PlayAnimation();
	}
	
	//// 設定
	m_settingWard = m_uiCanvas->CreateUI<UIIcon>(3);
	m_settingWard->Initialize("Assets/modelData/menu/settei.dds", 300.0f, 55.0f);
	m_settingWard->m_transform.m_localPosition = Vector3(-450.0f, -100.0f, 0.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		m_settingWard->AddAnimation(Hash32("settingWardColorAnimation"), std::move(colorAnimation));
		m_settingWard->PlayAnimation();
	}
	
	//// おわり
	m_endWard = m_uiCanvas->CreateUI<UIIcon>(4);
	m_endWard->Initialize("Assets/modelData/menu/owaru.dds", 300.0f, 55.0f);
	m_endWard->m_transform.m_localPosition = Vector3(-450.0f, -200.0f, 0.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		m_endWard->AddAnimation(Hash32("endWardColorAnimation"), std::move(colorAnimation));
		m_endWard->PlayAnimation();
	}
	
	//// 羽ペン
	m_hanePen = m_uiCanvas->CreateUI<UIIcon>(5);
	m_hanePen->Initialize("Assets/modelData/menu/hane.dds", 80.0f, 106.0f);
	m_hanePen->m_transform.m_localPosition = Vector3(-250.0f, 120.0f, 0.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::PingPong);
		m_hanePen->AddAnimation(Hash32("hanePenColorAnimation"), std::move(colorAnimation));
		m_hanePen->PlayAnimation();
	}
	

	//// 線 
	m_senPosition = Vector3(-450.0f, 65.0f, 0.0f);
	m_sen = m_uiCanvas->CreateUI<UIIcon>(6);
	m_sen->Initialize("Assets/modelData/menu/sen.dds", 250.0f, 11.0f);
	m_sen->m_transform.m_localPosition = Vector3(-450.0f, 65.0f, 0.0f);
	//// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::Linear, LoopMode::Once);
		m_sen->AddAnimation(Hash32("senTranslateAnimation"),std::move(colorAnimation));
		m_sen->PlayAnimation();
	}

	m_uiCanvas->m_transform.UpdateTransform();

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


	// @todo
	// 下線の座標を変える
	m_sen->m_transform.m_localPosition = m_senPosition + (Vector3(0.0f, -100.f, 0.0f) * m_currentSelectIndex);
	// 羽ペンの座標を変える
	float hanePenPosXList[] = { -250.0f,-285.0f,-350.0f,-325.0f };
	m_hanePen->m_transform.m_localPosition.x = hanePenPosXList[m_currentSelectIndex];
	m_hanePen->m_transform.m_localPosition.y = 120.0f +(-100.0f * m_currentSelectIndex);

	// 下線の大きさを文字の大きさに変える
	float senScaleList[] = { 1.4f, 1.1f, 0.6f, 0.8f };
	m_sen->m_transform.m_localScale = Vector3(senScaleList[m_currentSelectIndex], 1.0f, 1.0f);

	if (g_pad[0]->IsTrigger(enButtonA)) {
		// Aボタンが押された
		m_isSelected = true;
		/** メニュー表のカラーアニメーション */
		{
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, EasingType::Linear, LoopMode::Once);
			m_selectMenu->RemoveAnimation(Hash32("menuColorAnimation"));
			m_selectMenu->AddAnimation(Hash32("menuColorAnimation"), std::move(colorAnimation));
			m_selectMenu->PlayAnimation();
		}
		// 文字　ゲームスタート
		{
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, EasingType::Linear, LoopMode::Once);
			m_startWard->RemoveAnimation(Hash32("startWardColorAnimation"));
			m_startWard->AddAnimation(Hash32("startWardColorAnimation"), std::move(colorAnimation));
			m_startWard->PlayAnimation();
		}
		// 文字　操作方法
		{
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, EasingType::Linear, LoopMode::Once);
			m_guideWard->RemoveAnimation(Hash32("guideWardColorAnimation"));
			m_guideWard->AddAnimation(Hash32("guideWardColorAnimation"), std::move(colorAnimation));
			m_guideWard->PlayAnimation();
		}
		// 文字　設定
		{
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, EasingType::Linear, LoopMode::Once);
			m_settingWard->RemoveAnimation(Hash32("settingWardColorAnimation"));
			m_settingWard->AddAnimation(Hash32("settingWardColorAnimation"), std::move(colorAnimation));
			m_settingWard->PlayAnimation();
		}
		// 文字　おわり
		{
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, EasingType::Linear, LoopMode::Once);
			m_endWard->RemoveAnimation(Hash32("endWardColorAnimation"));
			m_endWard->AddAnimation(Hash32("endWardColorAnimation"), std::move(colorAnimation));
			m_endWard->PlayAnimation();
		}
		// 羽ペン
		{
			m_hanePen->m_uiAnimationList.clear();
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 0.5f, EasingType::Linear, LoopMode::Once);
			m_hanePen->RemoveAnimation(Hash32("hanePenColorAnimation"));
			m_hanePen->AddAnimation(Hash32("hanePenColorAnimation"), std::move(colorAnimation));
			m_hanePen->PlayAnimation();
		}
		// 下線
		{
			m_sen->m_uiAnimationList.clear();
			auto colorAnimation = std::make_unique<UIColorAnimation>();
			colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 1.0f, 0.0f), 0.5f, EasingType::Linear, LoopMode::Once);
			m_sen->RemoveAnimation(Hash32("senTranslateAnimation"));
			m_sen->AddAnimation(Hash32("senTranslateAnimation"), std::move(colorAnimation));
			m_sen->PlayAnimation();
		}
	}
	// Aボタンを押したかどうか
	if (m_isSelected){
		// アニメーションを待っている
		if (m_selectMenu->IsComplted()) {
			m_isChange = true;
			m_isSelected = false;
		}
	}

	/*if (!m_isPlayAnimation) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_selectMenu->m_color.w = 0.0f;
			m_selectMenu->PlayAnimation();
			m_isPlayAnimation = true;
		}
	}
	else {
		if (m_selectMenu->IsComplted()) {
			m_isChange = true;
		}
	}*/

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
			// プレイ人数選択
			//TitleScene::SetStartGame(true);
			request = enTitleMenuType_Play;
			return true;
		}
		case enSelectMenuType_Operation:
		{
			//コントローラーの説明が見れる
			request = enTitleMenuType_Cotrol;
			return true;
		}
		case enSelectMenuType_Setting:
		{
			// おばけの性格を変更できる
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
	auto* playerBack = m_uiCanvas->CreateUI<UIIcon>(0);
	playerBack->Initialize("Assets/modelData/menu/player_num.dds", 1700.0f, 1050.0f);
	playerBack->m_transform.m_localPosition = Vector3::Zero;

	// おばけとプレイヤーナンバーの初期化
	for (int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		// おばけ
		m_playerObake[i] = m_uiCanvas->CreateUI<UIIcon>(1);
		m_playerObake[i]->Initialize(titlePlayerSpriteInfoList[i].playerPath.c_str(), titlePlayerSpriteInfoList[i].width, titlePlayerSpriteInfoList[i].hight);
		m_playerObake[i]->m_transform.m_localPosition = Vector3(titlePlayerSpriteInfoList[i].playerPosition);
		// プレイヤーナンバー
		m_playerNumber[i] = m_uiCanvas->CreateUI<UIIcon>(2);
		m_playerNumber[i]->Initialize(titleIconSpriteInfoList[i].iconPath.c_str(), titleIconSpriteInfoList[i].npcWidth, titleIconSpriteInfoList[i].npcHight);
		m_playerNumber[i]->m_transform.m_localPosition = Vector3(titleIconSpriteInfoList[i].iconPosition);
	}


	// おばけ
	m_playerObake[0] = m_uiCanvas->CreateUI<UIIcon>(3);
	m_playerObake[0]->Initialize("Assets/modelData/menu/obake_hansup.dds", 300.0f, 300.0f);
	m_playerObake[0]->m_transform.m_localPosition = Vector3(-250.0f, -100.0f, 0.0f);
	
	// プレイヤーナンバー
	m_playerNumber[0] = m_uiCanvas->CreateUI<UIIcon>(4);
	m_playerNumber[0]->Initialize("Assets/modelData/UI/player/1P.dds", 125.0f, 75.0f);
	m_playerNumber[0]->m_transform.m_localPosition = Vector3(-250.0f, 100.0f, 0.0f);

	// おばけ
	m_playerObake[1] = m_uiCanvas->CreateUI<UIIcon>(5);
	m_playerObake[1]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f);
	m_playerObake[1]->m_transform.m_localPosition = Vector3(50.0f, -100.0f, 0.0f);
	
	// プレイヤーナンバー
	m_playerNumber[1] = m_uiCanvas->CreateUI<UIIcon>(6);
	m_playerNumber[1]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f);
	m_playerNumber[1]->m_transform.m_localPosition = Vector3(50.0f, 100.0f, 0.0f);

	// おばけ
	m_playerObake[2] = m_uiCanvas->CreateUI<UIIcon>(7);
	m_playerObake[2]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f);
	m_playerObake[2]->m_transform.m_localPosition = Vector3(350.0f, -100.0f, 0.0f);

	// プレイヤーナンバー
	m_playerNumber[2] = m_uiCanvas->CreateUI<UIIcon>(8);
	m_playerNumber[2]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f);
	m_playerNumber[2]->m_transform.m_localPosition = Vector3(350.0f, 100.0f, 0.0f);

	// おばけ
	m_playerObake[3] = m_uiCanvas->CreateUI<UIIcon>(9);
	m_playerObake[3]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f);
	m_playerObake[3]->m_transform.m_localPosition = Vector3(650.0f, -100.0f, 0.0f);
	
	// プレイヤーナンバー
	m_playerNumber[3] = m_uiCanvas->CreateUI<UIIcon>(10);
	m_playerNumber[3]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f);
	m_playerNumber[3]->m_transform.m_localPosition = Vector3(650.0f, 100.0f, 0.0f);

	// もどる
	auto* m_backObake = m_uiCanvas->CreateUI<UIIcon>(11);
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f);
	m_backObake->m_transform.m_localPosition = Vector3(-665.0f, -300.0f, 0.0f);

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
			m_playerObake[i]->Initialize(titlePlayerSpriteInfoList[i].upPath.c_str(), titlePlayerSpriteInfoList[i].width, titlePlayerSpriteInfoList[i].hight);
			m_playerObake[i]->m_transform.m_localPosition = Vector3(titlePlayerSpriteInfoList[i].playerPosition);
			
			// プレイヤー人数が増える
			m_playerNumber[i]->Initialize(titleIconSpriteInfoList[i].selectedIconPath.c_str(), titleIconSpriteInfoList[i].npcWidth, titleIconSpriteInfoList[i].npcHight);
			m_playerNumber[i]->m_transform.m_localPosition = Vector3(titleIconSpriteInfoList[i].iconPosition);
		}
		else {
			// おばけの手がさがる
			m_playerObake[i]->Initialize(titlePlayerSpriteInfoList[i].playerPath.c_str(), titlePlayerSpriteInfoList[i].width, titlePlayerSpriteInfoList[i].hight);
			m_playerObake[i]->m_transform.m_localPosition = Vector3(titlePlayerSpriteInfoList[i].playerPosition);

			// プレイヤー人数が減る
			m_playerNumber[i]->Initialize(titleIconSpriteInfoList[i].iconPath.c_str(), titleIconSpriteInfoList[i].npcWidth, titleIconSpriteInfoList[i].npcHight);
			m_playerNumber[i]->m_transform.m_localPosition = Vector3(titleIconSpriteInfoList[i].iconPosition);
		}
	}

	//// インゲームに行く
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	//TitleScene::SetStartGame(true);
	//	request = enTitleMenuType_StartTab;
	//}

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
	// スタートタブ
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//TitleScene::SetStartGame(true);
		request = enTitleMenuType_StartTab;
		return true;
	}

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
	auto* controlGuide = m_uiCanvas->CreateUI<UIIcon>(1);
	controlGuide->Initialize("Assets/modelData/menu/contlloer.dds", 1700.0f, 1050.0f);
	controlGuide->m_transform.m_localPosition = Vector3::Zero;

	// もどる
	auto* m_backObake = m_uiCanvas->CreateUI<UIIcon>(2);
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f);
	m_backObake->m_transform.m_localPosition = Vector3(-665.0f, -300.0f, 0.0f);

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
	auto* controlGuide = m_uiCanvas->CreateUI<UIIcon>(0);
	controlGuide->Initialize("Assets/modelData/menu/seikaku.dds", 1700.0f, 1050.0f);
	controlGuide->m_transform.m_localPosition = Vector3::Zero;

	//npc
	for (int i = 0; i < NPC_TYPE_NUM; i++)
	{
		// おばけ
		m_npcTypeObake[i] = m_uiCanvas->CreateUI<UIIcon>(1);
		m_npcTypeObake[i]->Initialize(titleNPCTypeSpriteInfoList[i].typePath.c_str(), titleNPCTypeSpriteInfoList[i].width, titleNPCTypeSpriteInfoList[i].hight);
		m_npcTypeObake[i]->m_transform.m_localPosition = Vector3(titleNPCTypeSpriteInfoList[i].npcPosition);

		// 性格
		m_npcTypeIcon[i] = m_uiCanvas->CreateUI<UIIcon>(2);
		m_npcTypeIcon[i]->Initialize(titleNPCIconSpriteInfoList[i].npcIconPath.c_str(), titleNPCIconSpriteInfoList[i].width, titleNPCIconSpriteInfoList[i].hight);
		m_npcTypeIcon[i]->m_transform.m_localPosition = Vector3(titleNPCIconSpriteInfoList[i].npcIconPosition);
	}
	// もどる
	auto* m_backObake = m_uiCanvas->CreateUI<UIIcon>(3);
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f);
	m_backObake->m_transform.m_localPosition = Vector3(-665.0f, -300.0f, 0.0f);

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
			m_npcTypeObake[i]->Initialize(titleNPCTypeSpriteInfoList[i].selectedTypePath.c_str(), titleNPCTypeSpriteInfoList[i].width, titleNPCTypeSpriteInfoList[i].hight);
			m_npcTypeObake[i]->m_transform.m_localPosition = Vector3(titleNPCTypeSpriteInfoList[i].npcPosition);
		}
		else {
			// おばけの手がさがる
			m_npcTypeObake[i]->Initialize(titleNPCTypeSpriteInfoList[i].typePath.c_str(), titleNPCTypeSpriteInfoList[i].width, titleNPCTypeSpriteInfoList[i].hight);
			m_npcTypeObake[i]->m_transform.m_localPosition = Vector3(titleNPCTypeSpriteInfoList[i].npcPosition);
		}
	}

	// メニュー選択
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		--m_npcTypeIndex;
		// 最小値
		if (m_npcTypeIndex < enNPCType_kind)
		{
			m_npcTypeIndex = enNPCType_kind; //範囲外にならないように調整
		}
	}
	else if (g_pad[0]->IsTrigger(enButtonDown))
	{
		++m_npcTypeIndex;
		// 最大値
		if (m_npcTypeIndex >= enNPCType_Max)
		{
			m_npcTypeIndex = enNPCType_Max - 1; //範囲外にならないように調整
		}
	}

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

SelectTab::SelectTab()
{
}

SelectTab::~SelectTab()
{
}


bool SelectTab::Start()
{
	m_uiCanvas = std::make_unique<UICanvas>();


	// 簡易的にフェードを付ける
	auto* simpleFade = m_uiCanvas->CreateUI<UIIcon>(0);
	simpleFade->Initialize("Assets/modelData/tab/fade_tab.dds", 1920.0f, 1080.0f);
	simpleFade->m_transform.m_localPosition = Vector3::Zero;

	// タブの背景画像
	auto* backTab = m_uiCanvas->CreateUI<UIIcon>(1);
	backTab->Initialize("Assets/modelData/tab/back_tab.dds", 1000.0f, 500.0f);
	backTab->m_transform.m_localPosition = Vector3::Zero;
	// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::EaseIn, LoopMode::Once);
		backTab->AddAnimation(Hash32("backTabColorAnimation"), std::move(colorAnimation));
		backTab->PlayAnimation();
	}

	//// はいボタン
	m_yesButton = m_uiCanvas->CreateUI<UIIcon>(2);
	m_yesButton->Initialize("Assets/modelData/tab/button_tab.dds", 400.0f, 153.0f);
	m_yesButton->m_transform.m_localPosition = Vector3(-250.0f, -90.0f, 0.0f);
	// アニメーション
	{
		//auto colorAnimation = std::make_unique<UIColorAnimation>();
		//colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::EaseIn, LoopMode::Once);
		//m_yesButton->AddAnimation(Hash32("m_yesButtonColorAnimation"),std::move(colorAnimation));
		//m_yesButton->PlayAnimation();
		//m_yesButton->m_uiAnimationList.clear();
	}
	//選択中のスケールアニメーション
	{
		auto scaleAnimation = std::make_unique<UIScaleAnimation>();
		scaleAnimation->SetParameter(Vector3::One, Vector3(1.2f, 1.2f, 1.2f), 0.4f, EasingType::EaseIn, LoopMode::Once);
		m_yesButton->AddAnimation(Hash32("m_yesButtonScaleAnimation"), std::move(scaleAnimation));
		m_yesButton->StopSpriteAnimation();
		//m_yesButton->m_uiAnimationList.clear();
	}
	m_yesButton->PlayAnimation();

	//// いいえボタン
	m_noButton = m_uiCanvas->CreateUI<UIIcon>(3);
	m_noButton->Initialize("Assets/modelData/tab/button_tab.dds", 400.0f, 153.0f);
	m_noButton->m_transform.m_localPosition = Vector3(250.0f, -90.0f, 0.0f);
	// アニメーション
	{
		//auto colorAnimation = std::make_unique<UIColorAnimation>();
		//colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::EaseIn, LoopMode::Once);
		//m_noButton->AddAnimation(Hash32("m_noButtonColorAnimation"), std::move(colorAnimation));
	   // m_noButton->PlayAnimation();
		//m_noButton->m_uiAnimationList.clear();
	}
	//選択中のスケールアニメーション
	{
		auto scaleAnimation = std::make_unique<UIScaleAnimation>();
		scaleAnimation->SetParameter(Vector3::One, Vector3(1.2f, 1.2f, 1.2f), 0.2f, EasingType::EaseIn, LoopMode::Once);
		m_noButton->AddAnimation(Hash32("m_noButtonScaleAnimation"), std::move(scaleAnimation));
		m_noButton->StopSpriteAnimation();
		//m_noButton->m_uiAnimationList.clear();
	}
	//m_noButton->PlayAnimation();


	//// プレイする？
	auto* playWardTab = m_uiCanvas->CreateUI<UIIcon>(7);
	playWardTab->Initialize("Assets/modelData/tab/play_tab.dds", 800.0f, 60.0f);
	playWardTab->m_transform.m_localPosition = Vector3(0.0f, 100.0f, 0.0f);
	// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::EaseIn, LoopMode::Once);
		playWardTab->AddAnimation(Hash32("playWardTabColorAnimation"), std::move(colorAnimation));
		playWardTab->PlayAnimation();
		playWardTab->m_uiAnimationList.clear();
	}

	//// 左 いいえ
	auto* noWardTab = m_uiCanvas->CreateUI<UIIcon>(6);
	noWardTab->Initialize("Assets/modelData/tab/iie_tab.dds", 150.0f, 46.0f);
	noWardTab->m_transform.m_localPosition = Vector3(-250.0f, -90.0f, 0.0f);
	// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::EaseIn, LoopMode::Once);
		noWardTab->AddAnimation(Hash32("noWardTabColorAnimation"), std::move(colorAnimation));
		noWardTab->PlayAnimation();
		//noWardTab->m_uiAnimationList.clear();
	}
	//// 右 はい
	auto* yesWardTab = m_uiCanvas->CreateUI<UIIcon>(4);
	yesWardTab->Initialize("Assets/modelData/tab/hai_tab.dds", 100.0f, 44.0f);
	yesWardTab->m_transform.m_localPosition = Vector3(250.0f, -90.0f, 0.0f);
	// アニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, EasingType::EaseIn, LoopMode::Once);
		yesWardTab->AddAnimation(Hash32("yesWardTabColorAnimation"), std::move(colorAnimation));
		yesWardTab->PlayAnimation();
		//yesWardTab->m_uiAnimationList.clear();
	}

	//// 選択している枠
	m_wakuTab = m_uiCanvas->CreateUI<UIIcon>(5);
	m_wakuTab->Initialize("Assets/modelData/tab/waku_tab.dds", 400.0f, 153.0f);
	m_wakuTab->m_transform.m_localPosition = Vector3(-250.0f, -90.0f, 0.0f);
	// カラーアニメーション
	{
		auto colorAnimation = std::make_unique<UIColorAnimation>();
		colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 0.5f, EasingType::EaseIn, LoopMode::Once);
		m_wakuTab->AddAnimation(Hash32("m_wakuTabColorAnimation"), std::move(colorAnimation));
		m_wakuTab->StopSpriteAnimation();
		//m_wakuTab->PlayAnimation();
		//m_wakuTab->m_uiAnimationList.clear();
	}
	//スケールアニメーション
	{
		auto scaleAnimation = std::make_unique<UIScaleAnimation>();
		scaleAnimation->SetParameter(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.2f, 1.2f, 1.2f), 0.5f, EasingType::EaseIn, LoopMode::Once);
		m_wakuTab->AddAnimation(Hash32("m_wakuTabScaleAnimation"), std::move(scaleAnimation));
		m_wakuTab->StopSpriteAnimation();
		//m_wakuTab->PlayAnimation();
		//m_wakuTab->m_uiAnimationList.clear();
	}
	m_wakuTab->PlayAnimation();


	return true;
}

void SelectTab::Update()
{
	// ゲームをスタートするか選択する
	int oldIndex = m_currentTabSelectindex;
	UpdateSelectTabIndex();

	// 枠の座標を変える
	float wakuTabPosXList[] = { -250.0f,250.0f };
	m_wakuTab->m_transform.m_localPosition.x = wakuTabPosXList[m_currentTabSelectindex];

	// 選択に変更があったか
	if (oldIndex != m_currentTabSelectindex)
	{
		m_wakuTab->m_transform.m_localScale = Vector3::One;

		m_wakuTab->m_uiAnimationList.clear();
		m_yesButton->m_uiAnimationList.clear();
		m_noButton->m_uiAnimationList.clear();
		if (m_currentTabSelectindex == enSelectTab_Yes)
		{
			m_yesButton->m_transform.m_localScale = Vector3::One;
			/** スケールアニメーション */
			{
				auto scaleAnimation = std::make_unique<UIScaleAnimation>();
				scaleAnimation->SetParameter(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.2f, 1.2f, 1.2f), 0.2f, EasingType::EaseIn, LoopMode::Once);
				m_wakuTab->AddAnimation(Hash32("m_wakuTabScaleAnimation"), std::move(scaleAnimation));
			}
			/** カラーアニメーション */
			{
				auto colorAnimation = std::make_unique<UIColorAnimation>();
				colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 0.2f, EasingType::EaseIn, LoopMode::Once);
				m_wakuTab->AddAnimation(Hash32("m_wakuTabColorAnimation"), std::move(colorAnimation));
			}
			m_wakuTab->PlayAnimation();
			/** スケールアニメーション */
			{
				auto scaleAnimation = std::make_unique<UIScaleAnimation>();
				scaleAnimation->SetParameter(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.2f, 1.2f, 1.2f), 0.2f, EasingType::EaseIn, LoopMode::Once);
				m_noButton->AddAnimation(Hash32("m_noButtonColorAnimation"), std::move(scaleAnimation));
			}
			/** カラーアニメーション */
			{
				// auto colorAnimation = std::make_unique<UIColorAnimation>();
				// colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.2f, EasingType::EaseIn, LoopMode::Once);
				// m_noButton->AddAnimation(Hash32("m_noButtonColorAnimation"), std::move(colorAnimation));
			}
			m_noButton->PlayAnimation();
		}
		else if (m_currentTabSelectindex == enSelectTab_No)
		{
			m_noButton->m_transform.m_localScale = Vector3::One;
			/** スケールアニメーション */
			{
				auto scaleAnimation = std::make_unique<UIScaleAnimation>();
				scaleAnimation->SetParameter(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.2f, 1.2f, 1.2f), 0.2f, EasingType::EaseIn, LoopMode::Once);
				m_wakuTab->AddAnimation(Hash32("m_wakuTabScaleAnimation"), std::move(scaleAnimation));
			}
			/** カラーアニメーション */
			{
				auto colorAnimation = std::make_unique<UIColorAnimation>();
				colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 0.2f, EasingType::EaseIn, LoopMode::Once);
				m_wakuTab->AddAnimation(Hash32("m_wakuTabColorAnimation"), std::move(colorAnimation));
			}
			m_wakuTab->PlayAnimation();
			/** スケールアニメーション */
			{
				auto scaleAnimation = std::make_unique<UIScaleAnimation>();
				scaleAnimation->SetParameter(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.2f, 1.2f, 1.2f), 0.2f, EasingType::EaseIn, LoopMode::Once);
				m_yesButton->AddAnimation(Hash32("m_yesButtonScaleAnimation"), std::move(scaleAnimation));
			}
			/** カラーアニメーション */
			{
				//auto colorAnimation = std::make_unique<UIColorAnimation>();
				//colorAnimation->SetParameter(Vector4(1.0f, 1.0f, 1.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 1.2f, EasingType::EaseIn, LoopMode::Once);
				//m_yesButton->AddAnimation(Hash32("m_yesButtonColorAnimation"), std::move(colorAnimation));
			}
			m_yesButton->PlayAnimation();
		}
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

void SelectTab::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

bool SelectTab::CanChange(int& reqest)
{
	// itranaikkamo

	//if (m_isBack) {
	//	request = enTitleMenuType_Select;
	//	return true;
	//}

	switch (m_currentTabSelectindex)
	{
		/** TODO:　要修正 */
	case enSelectTab_No:
		if (m_isBack
			|| g_pad[0]->IsTrigger(enButtonA)) {
			reqest = enTitleMenuType_Play;
			return true;
		}
		break;
	case enSelectTab_Yes:
		if (g_pad[0]->IsTrigger(enButtonA)) {
			TitleScene::SetStartGame(true);
			break;
		}
		break;
	default:
		K2_ASSERT(false, "未実装");
		break;
	}

	return false;
}


void SelectTab::UpdateSelectTabIndex()
{
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		--m_currentTabSelectindex;
		// 最小値
		if (m_currentTabSelectindex < enSelectTab_No)
		{
			m_currentTabSelectindex = enSelectTab_No; //範囲外にならないように調整
		}
	}
	else if (g_pad[0]->IsTrigger(enButtonRight))
	{
		++m_currentTabSelectindex;
		// 最大値
		if (m_currentTabSelectindex >= enSelectTab_Yes)
		{
			m_currentTabSelectindex = enSelectTab_Yes; //範囲外にならないように調整
		}
	}
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
	m_titleMenu->Update();

	// タイトル画面の3D.tkm
	m_titleBack = std::make_unique<ModelRender>();
	m_titleBack->Init("Assets/modelData/Ground/title_back.tkm");
	m_titleBack->SetPosition(Vector3(0.0f, 0.0f, 30.0f));
	m_titleBack->SetScale(Vector3::One * 0.4f);
	m_titleBack->Update();

	// 看板を仮表示
	/*m_titleRender = std::make_unique<SpriteRender>();
	m_titleRender->Init("Assets/modelData/title/kanban.dds",500.0f,657.0f);
	m_titleRender->SetPosition(Vector3(-600.0f, 250.0f, 0.0f));
	m_titleRender->SetScale(Vector3::One);
	m_titleRender->Update();*/


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
	ITitleMenu* titleMenu = nullptr;
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
	case enTitleMenuType_StartTab:
	{
		titleMenu = new SelectTab();
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
	m_titleMenu = std::unique_ptr<ITitleMenu>(titleMenu);
}