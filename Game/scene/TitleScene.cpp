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
		TitleSpriteInformation("Assets/modelData/title/titleBack.dds", Vector3::Zero, MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT),
		TitleSpriteInformation("Assets/modelData/title/titlelogo.dds", Vector3(0.0f, 100.0f, 0.0f), 800.0f, 150.0f),
		TitleSpriteInformation("Assets/modelData/title/push_a.dds", Vector3(0.0f, -150.0f, 0.0f), 300, 70),
	};
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

	std::vector<Vector4> targetAlphaList = { Vector4(0.8f, 0.8f, 0.8f, 1.0f), Vector4(0.6f, 0.6f, 0.6f, 0.4f), Vector4(0.8f, 0.8f, 0.8f, 1.0f) };
	std::vector<float> timeList = { 0.8f,0.8f };
	m_buttonAnimation = std::make_unique<ColorSpriteAnimation>(&m_spriteRender[enTitleSpriteKind_ButtonA], true, timeList, targetAlphaList);
	m_buttonAnimation->Play();

	SoundManager::Get().PlayBGM(enSoundKind_Title);

	
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