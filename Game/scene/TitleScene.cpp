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

	static const TitleSpriteInformation titleSpriteInfoList[enTitleSpriteKind_Max] = {
		//TitleSpriteInformation("Assets/modelData/title/titleBack.dds", Vector3::Zero, MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT),
		TitleSpriteInformation("Assets/modelData/title/titlelog.dds", Vector3(0.0f, 300.0f, 0.0f), 800.0f, 150.0f),
		TitleSpriteInformation("Assets/modelData/title/push_a.dds", Vector3(0.0f, -150.0f, 0.0f), 300, 70),
	};
}


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
	for (int i = 0; i < enTitleSpriteKind_Max; i++) {
		const auto& info = titleSpriteInfoList[i];
		m_spriteRender[i].Init(info.assetPath.c_str(), info.width, info.hight);
		m_spriteRender[i].SetPosition(info.position);
	}

	m_player = NewGO<Player>(0, "player");
	m_player->m_transform.m_localPosition.Set(100.0f, 0.0f, 0.0f);
	m_player->m_transform.m_localRotation.SetRotationDegY(180.0f);
	m_player->m_transform.m_localScale.Set(1.5f, 1.5f, 1.5f);

	std::vector<Vector4> targetAlphaList = { Vector4(0.8f, 0.8f, 0.8f, 1.0f), Vector4(0.6f, 0.6f, 0.6f, 0.4f), Vector4(0.8f, 0.8f, 0.8f, 1.0f) };
	std::vector<float> timeList = { 0.8f,0.8f };
	m_buttonAnimation = std::make_unique<ColorSpriteAnimation>(&m_spriteRender[enTitleSpriteKind_ButtonA], true, timeList, targetAlphaList);
	m_buttonAnimation->Play();

	// @todo for タイトル画面の3D.tkm
	m_titleBack = std::make_unique<ModelRender>();
	m_titleBack->Init("Assets/modelData/Ground/title_back.tkm");
	m_titleBack->SetPosition(Vector3(0.0f, 0.0f, 30.0f));
	m_titleBack->SetScale(Vector3::One * 0.4f);
	m_titleBack->Update();

	// @todo for 看板を仮表示
	m_titleRender = std::make_unique<SpriteRender>();
	m_titleRender->Init("Assets/modelData/title/kanban.dds",500.0f,657.0f);
	m_titleRender->SetPosition(Vector3(-600.0f, 250.0f, 0.0f));
	m_titleRender->SetScale(Vector3::One);
	m_titleRender->Update();


	SoundManager::Get().PlayBGM(enSoundKind_Title);

	// ライト調整
	g_sceneLight->SetDirectionLight(0, Vector3(1.0f, -1.0f, 0.0f), Vector3(0.8f, 0.8f, 0.8f));
	g_sceneLight->SetAmbinet(Vector3(0.2f, 0.2f, 0.2f));

	return true;
}


void TitleScene::Update()
{
	if (!m_isRequestNext) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			SoundManager::Get().PlaySE(enSoundKind_Button);
			m_isRequestNext = true;
		}
	}

	m_buttonAnimation->Update();

	for (int i = 0; i < enTitleSpriteKind_Max; i++) {
		m_spriteRender[i].Update();
	}
}


void TitleScene::Render(RenderContext& rc)
{
	for (int i = 0; i < enTitleSpriteKind_Max; i++) {
		m_spriteRender[i].Draw(rc);
	}

	// @todo for タイトル画面
	m_titleBack->Draw(rc);
	// @todo for 看板の仮表示
	m_titleRender->Draw(rc);
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