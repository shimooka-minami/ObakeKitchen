#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start() override;
	void Update() override;
	void Render(RenderContext&rc) override;
	
	//変数
	Player* m_player; //プレイヤー
	Vector3 m_toCameraPos; //注視点から視点に向かうベクトル
};

