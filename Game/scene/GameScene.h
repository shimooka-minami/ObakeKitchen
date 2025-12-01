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
class UIScore;
class TimeKeeper;
class UITimer;
class UIPlayerNumber;

class NPCController;


/**
 * インゲーム中のシーン
 */
class GameScene : public IScene
{
	appScene(GameScene);

private:
	GameCamera* m_gameCamera = nullptr;
	BackGround* m_backGround = nullptr;

	// @todo for test
	//UIGauge* m_uiGauge = nullptr;
	UIScore* m_uiScore = nullptr;
	UITimer* m_uiTimer = nullptr;

	std::unique_ptr<TimeKeeper> m_timeKeeper;

	std::array<Player*, MAX_PLAYER_NUM> m_playerList;
	std::array<PlayerController*, MAX_PLAYER_NUM> m_playerControllerList;
	std::array<NPCController*, MAX_PLAYER_NUM> m_npcControllerList;
	std::array<UIPlayerNumber*, MAX_PLAYER_NUM> m_uiPlayerNumber;

	/** NewGOしたオブジェクトを削除するために対象を覚えるリスト */
	std::vector<IGameObject*> m_deleteList;

	// @todo for test
	std::vector<SPointLight*> m_pointLightList;


	/** 次のシーンに行く変数 */
	bool m_isNextScene = false;

public:
	GameScene();
	virtual ~GameScene();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

	virtual bool RequestScene(uint32_t& id, float& waitTime) override;
};