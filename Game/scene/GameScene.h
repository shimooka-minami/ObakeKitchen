/**
 * GameScene.h
 * インゲーム中のシーン
 */
#pragma once
#include "IScene.h"


class Player;
class PlayerController;
class GameCamera;
class BackGround;


/**
 * インゲーム中のシーン
 */
class GameScene : public IScene
{
	appScene(GameScene);

private:
	PlayerController* m_playerContoller = nullptr;
	GameCamera* m_gameCamera = nullptr;
	BackGround* m_backGround = nullptr;

	// @todo for test
	//UIGauge* m_uiGauge = nullptr;


	ModelRender m_modelRender; //モデル描画

	std::array<Player*, MAX_PLAYER_NUM> m_playerList;

public:
	GameScene();
	virtual ~GameScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime) override;
};

