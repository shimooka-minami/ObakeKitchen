#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class PlayerController;
class GameCamera;
class BackGround;


class Game : public IGameObject
{
private:
	PlayerController* m_playerContoller = nullptr;
	GameCamera* m_gameCamera = nullptr;
	BackGround* m_backGround = nullptr;


	ModelRender m_modelRender; //ƒ‚ƒfƒ‹•`‰æ

	std::array<Player*, MAX_PLAYER_NUM> m_playerList;


public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);


	
	
};

