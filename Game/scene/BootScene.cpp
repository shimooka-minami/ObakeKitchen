#include "stdafx.h"
#include "BootScene.h"
#include "TitleScene.h"
#include "sound/SoundManager.h"


namespace
{
	enum EnBootKind
	{
		enBootKind_Game,
		enBootKind_LogoA,
		enBootKind_LogoB,
		enBootKind_Max,
	};
	struct BootInformation
	{
		std::string assetPath;
		float time;
		float shortTime;
		enSoundKind voiceKind;
		//
		BootInformation(const std::string& path, const float t, const float st, const enSoundKind vKind)
			: assetPath(path)
			, time(t)
			, shortTime(st)
			, voiceKind(vKind)

		{}
	};
	static const BootInformation bootInfoList[] = {
		BootInformation("Assets/modelData/title/notitle.dds", 2.0f, 0.5f, enSoundKind_None),
		BootInformation("Assets/modelData/title/kawahara.dds", 2.0f, 0.5f, enSoundKind_BootA),
		BootInformation("Assets/modelData/title/kbc_games.dds", 2.0f, 0.5f, enSoundKind_BootB),
	};

	constexpr float MAX_SPRITE_WIDTH = 1920.0f;
	constexpr float MAX_SPRITE_HIGHT = 1080.0f;
}


BootScene::BootScene()
{
}


BootScene::~BootScene()
{
}


bool BootScene::Start()
{
	// 初期設定
	Change();

	return true;
}


void BootScene::Update()
{
	if (m_spriteRender) {
		m_spriteRender->Update();
	}
	if (CanChange()) {
		Change();
		m_elapsedTime = 0.0f;
	} else {
		const float deltaTime = g_gameTime->GetFrameDeltaTime();
		m_elapsedTime += deltaTime;
	}
}


void BootScene::Render(RenderContext& rc)
{
	if (m_spriteRender) {
		m_spriteRender->Draw(rc);
	}
}


bool BootScene::RequestScene(uint32_t& id)
{
	if (m_currentIndex >= enBootKind_Max) {
		if (CanChange()) {
			id = TitleScene::ID();
			return true;
		}
	}
	return false;
}


void BootScene::Change()
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


bool BootScene::CanChange() const
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