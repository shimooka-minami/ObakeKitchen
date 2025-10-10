/**
 * StartupScene.cpp
 * スタートアップシーン
 */
#include "stdafx.h"
#include "StartupScene.h"
#include "TitleScene.h"
#include "sound/SoundManager.h"


namespace
{
	enum EnStartupKind
	{
		enBootKind_Game,
		enBootKind_LogoA,
		enBootKind_LogoB,
		enBootKind_Max,
	};
	struct StartupInformation
	{
		std::string assetPath;
		float time;
		float shortTime;
		enSoundKind voiceKind;
		//
		StartupInformation(const std::string& path, const float t, const float st, const enSoundKind vKind)
			: assetPath(path)
			, time(t)
			, shortTime(st)
			, voiceKind(vKind)

		{
		}
	};
	static const StartupInformation bootInfoList[] = {
		StartupInformation("Assets/modelData/title/notitle.dds", 2.5f, 0.5f, enSoundKind_None),
		StartupInformation("Assets/modelData/title/kawahara.dds", 2.5f, 0.5f, enSoundKind_BootA),
		StartupInformation("Assets/modelData/title/kbc_games.dds", 2.5f, 0.5f, enSoundKind_BootB),
	};

	constexpr float MAX_SPRITE_WIDTH = 1920.0f;
	constexpr float MAX_SPRITE_HIGHT = 1080.0f;
}


StartupScene::StartupScene()
{
}


StartupScene::~StartupScene()
{
}


bool StartupScene::Start()
{
	// 初期設定
	Change();

	return true;
}


void StartupScene::Update()
{
	if (m_spriteRender) {
		m_spriteRender->Update();
	}
	if (CanChange()) {
		Change();
		m_elapsedTime = 0.0f;
	}
	else {
		const float deltaTime = g_gameTime->GetFrameDeltaTime();
		m_elapsedTime += deltaTime;
	}
}


void StartupScene::Render(RenderContext& rc)
{
	if (m_spriteRender) {
		m_spriteRender->Draw(rc);
	}
}


bool StartupScene::RequestScene(uint32_t& id)
{
	if (m_currentIndex >= enBootKind_Max) {
		if (CanChange()) {
			id = TitleScene::ID();
			return true;
		}
	}
	return false;
}


void StartupScene::Change()
{
	if (m_spriteRender) {
		delete m_spriteRender;
		m_spriteRender = nullptr;
	}
	if (m_currentIndex >= enBootKind_Max) {
		return;
	}

	const auto& bootInfo = bootInfoList[m_currentIndex++];

	m_spriteRender = new SpriteRender();
	m_spriteRender->Init(bootInfo.assetPath.c_str(), MAX_SPRITE_WIDTH, MAX_SPRITE_HIGHT);

	m_changeTime = bootInfo.time;
	m_shortChangeTime = bootInfo.shortTime;

	if (bootInfo.voiceKind != enSoundKind_None) {
		SoundManager::Get().PlaySE(bootInfo.voiceKind);
	}
}


bool StartupScene::CanChange() const
{
	// 指定した経過時間を過ぎているなら変更可能
	if (m_elapsedTime >= m_changeTime) {
		return true;
	}
	// 一定時間を過ぎていて何かボタンを押したなら切り替え可能
	if (m_elapsedTime >= m_shortChangeTime) {
		if (g_pad[0]->IsPressAnyKey()) {
			return true;
		}
	}
	return false;
}