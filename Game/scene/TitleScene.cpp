#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "sound/SoundManager.h"

// @todo for test
#include "ui/UIBase.h"

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
		//
		TitleSpriteInformation(const std::string& path, const Vector3& pos, const float w, const float h)
			: assetPath(path)
			, position(pos)
			, width(w)
			, hight(h)
		{
		}
	};

	static const TitleSpriteInformation titleSpriteInfoList[enTitleSpriteKind_Max] = {
		TitleSpriteInformation("Assets/modelData/title/title1.dds", Vector3::Zero, MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT),
		TitleSpriteInformation("Assets/modelData/title/push_a.dds", Vector3(0.0f, -300.0f, 0.0f), 300, 100),
	};

	// @todo for test
	static UICanvas* canvasTest = nullptr;
}


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
	SoundManager::Get().StopBGM();
}


bool TitleScene::Start()
{
	for (int i = 0; i < enTitleSpriteKind_Max; i++) {
		const auto& info = titleSpriteInfoList[i];
		m_spriteRender[i].Init(info.assetPath.c_str(), info.width, info.hight);
		m_spriteRender[i].SetPosition(info.position);
	}

	m_buttonAnimation = std::make_unique<ScaleSpriteAnimation>(&m_spriteRender[enTitleSpriteKind_ButtonA], 1.5f, true, Vector2(1.0f, 1.0f), Vector2(1.3f, 1.3f));

	SoundManager::Get().PlayBGM(enSoundKind_Title);

	// @todo for test
	canvasTest = new UICanvas();
	canvasTest->m_transform.m_localPosition = Vector3(500.0f, 0.0f, 0.0f);
	auto* uiIcon = canvasTest->CreateUI<UIIcon>();
	uiIcon->Initialize("Assets/ui/hukidashi.dds", 100.0f, 100.0f, Vector3(-100.0f, 50.0f, 0.0f), Vector3::One, Quaternion::Identity);
	uiIcon = canvasTest->CreateUI<UIIcon>();
	uiIcon->Initialize("Assets/ui/tomato.dds", 80.0f, 80.0f, Vector3(-150.0f, 50.0f, 0.0f), Vector3::One, Quaternion::Identity);

	return true;
}


void TitleScene::Update()
{
	if (!isRequestNext) {
		if (g_pad[0]->IsPress(enButtonA)) {
			SoundManager::Get().PlaySE(enSoundKind_Button);
			isRequestNext = true;
		}
	}

	m_buttonAnimation->Update();

	for (int i = 0; i < enTitleSpriteKind_Max; i++) {
		m_spriteRender[i].Update();
	}

	// @todo for test
	if (g_pad[0]->IsPress(enButtonDown)) {
		canvasTest->m_transform.m_localPosition.y++;
	}
	canvasTest->Update();
}


void TitleScene::Render(RenderContext& rc)
{
	for (int i = 0; i < enTitleSpriteKind_Max; i++) {
		m_spriteRender[i].Draw(rc);
	}

	// @todo for test
	canvasTest->Render(rc);
}


bool TitleScene::RequestScene(uint32_t& id, float& waitTime)
{
	if (isRequestNext) {
		id = GameScene::ID();
		waitTime = 3.0f;
		return true;
	}
	return false;
}