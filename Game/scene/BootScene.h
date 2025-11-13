/**
 * BootScene.h
 * 起動画面のシーン
 * NOTE: デバッグ用でシーンの遷移を簡単にしている
 */
#pragma once
#include "IScene.h"


enum EnSceneKind
{
	enSceneKind_Default,
	enSceneKind_Boot = enSceneKind_Default,
	enSceneKind_Title,
	enSceneKind_Game,
	enSceneKind_Result,
	enSceneKind_Max,
};


/** 起動シーン */
class BootScene : public IScene
{
	appScene(BootScene);


private:
	/** 遷移をリクエストする先のシーンID */
	uint32_t m_requestSceneId = INVALID_SCENE_ID;
	/** シーン選択表示用 */
	FontRender m_sceneText[enSceneKind_Max];
	/** どれを選択しているかわかるようにアイコン */
	SpriteRender m_selecterRender;
	int m_selectIndex = enSceneKind_Default;


public:
	BootScene();
	virtual ~BootScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime)  override;
};