#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "sound/SoundManager.h"

// @todo for test
#include "ui/UIBase.h"
#include "actor/Player.h"

namespace
{
	constexpr float MAX_SPRITE_WIDTH = 1920.0f;
	constexpr float MAX_SPRITE_HIGHT = 1080.0f;

	struct TitleSpriteInformation
	{
		std::string assetPath;
		Vector3 position;
		float width;
		float hight;
		//タイトルスプライト情報
		TitleSpriteInformation(const std::string& path, const Vector3& pos, const float w, const float h)
			: assetPath(path)
			, position(pos)
			, width(w)
			, hight(h)
		{
		}
	};

	//static const TitleSpriteInformation titleSpriteInfoList[enTitleSpriteKind_Max] = {
	//	//TitleSpriteInformation("Assets/modelData/title/titleBack.dds", Vector3::Zero, MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT),
	//	//TitleSpriteInformation("Assets/modelData/title/titlelog.dds", Vector3(0.0f, 300.0f, 0.0f), 800.0f, 150.0f),
	//	//TitleSpriteInformation("Assets/modelData/title/push_a.dds", Vector3(0.0f, -150.0f, 0.0f), 300, 70),
	//};
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
		std::vector<Vector3> targetTanslateList = { Vector3::Zero, Vector3(0.0f, 600.0f, 0.0f) };
		std::vector<float> timeList = { 1.0f };
		auto* titleAnimation = new TranslateOffsetSpriteAnimation(m_titleIcon->GetSpriteRender(), false, timeList, targetTanslateList, &m_titleIcon->m_transform);
		m_titleIcon->AddSpriteAnimation(titleAnimation);
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
	} else {
		m_isChange = true;
	}

	m_uiCanvas->Update();
}


void TitleStartMenu::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}


bool TitleStartMenu::CanChange()
{
	return m_isChange;
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
		m_selectMenu->GetSpriteRender()->SetMulColor(Vector4(1.0f,1.0f,1.0f,0.0f));
	
	
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
			m_currentSelectIndex = enSelectMenuType_Num -1; //範囲外にならないように調整
		}
	}

	// 下線の座標を変える
	m_sen->m_transform.m_localPosition = m_senPosition + (Vector3(0.0f, -100.f, 0.0f) * m_currentSelectIndex);
	// 羽ペンの座標を変える
	m_hanePen->m_transform.m_localPosition = m_penPosition + (Vector3(0.0f, -100.0f, 0.0f) * m_currentSelectIndex);

	// 下線の大きさを文字の大きさに変える
	float senScaleList[] = { 1.4f, 1.1f, 0.6f, 0.8f };
	m_sen->m_transform.m_localScale = Vector3(senScaleList[m_currentSelectIndex], 1.0f, 1.0f);


	if (!m_selectMenu->IsCompleted()) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_selectMenu->PlaySpriteAnimation();
		}
	}
	else {
		m_isChange = true;
	}

	m_uiCanvas->Update();
}


void TitleSelectMenu::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}


bool TitleSelectMenu::CanChange()
{
	if (m_isChange)
	{
		return true;
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

	// おばけ
	m_playerObake[0] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerObake[0]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3(-250.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// プレイヤーナンバー
	m_playerNumber[0] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerNumber[0]->Initialize("Assets/modelData/UI/player/1P.dds", 125.0f, 75.0f, Vector3(-250.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// おばけ
	m_playerObake[1] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerObake[1]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3(  50.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// プレイヤーナンバー
	m_playerNumber[1] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerNumber[1]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f, Vector3(50.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// おばけ
	m_playerObake[2] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerObake[2]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3( 350.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// プレイヤーナンバー
	m_playerNumber[2] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerNumber[2]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f, Vector3(350.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	// おばけ
	m_playerObake[3] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerObake[3]->Initialize("Assets/modelData/menu/karioba.dds", 300.0f, 300.0f, Vector3( 650.0f, -100.0f, 0.0f), Vector3::One, Quaternion::Identity);
	// プレイヤーナンバー
	m_playerNumber[3] = m_uiCanvas->CreateUI<UIIcon>();
	m_playerNumber[3]->Initialize("Assets/modelData/UI/player/npc.dds", 200.0f, 110.0f, Vector3(650.0f, 100.0f, 0.0f), Vector3::One, Quaternion::Identity);

	


	return true;
}

void TitlePlayerSelectMenu::Update()
{
	for (int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		if (g_pad[i]->IsTrigger(enButtonA))
		{
			m_isPlayerConected[i] = true;
		}
	}
	m_uiCanvas->Update();
}

void TitlePlayerSelectMenu::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

bool TitlePlayerSelectMenu::CanChange()
{
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
	m_backObake->Initialize("Assets/modelData/menu/back_obake.dds", 250.0f, 250.0f, Vector3(-650.0f,-300.0f,0.0f), Vector3::One, Quaternion::Identity);

	return true;
}

void TitleControlGuide::Update()
{
	m_uiCanvas->Update();
}

void TitleControlGuide::Render(RenderContext& rc)
{
	m_uiCanvas->Render(rc);
}

bool TitleControlGuide::CanChange()
{
	return false;
}




/**************************************************/


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
	if (m_currentMenu >= enTitleMenuType_Num)
	{
		if (!m_isRequestNext) {

			if (g_pad[0]->IsTrigger(enButtonA)) {
				SoundManager::Get().PlaySE(enSoundKind_Button);
				m_isRequestNext = true;
			}
		}
	}
	//for (int i = 0; i < enTitleSpriteKind_Max; i++) {
	// m_spriteRender[i].Update();
	//}
	if (m_currentMenu < enTitleMenuType_Num) {
		if (m_titleMenu->CanChange()) {
			// 次のメニューへ
			++m_currentMenu;
			ChangeTitleMenu();
		}
	}
	m_titleMenu->Update();
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
		default:
		{
			K2_ASSERT(false, "Menuを追加してください");
		}
	}
	titleMenu->Start();
	m_titleMenu = std::unique_ptr<ITtitleMenu>(titleMenu);
}