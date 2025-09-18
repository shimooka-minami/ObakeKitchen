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
	
	//�ϐ�
	Player* m_player; //�v���C���[
	Vector3 m_toCameraPos; //�����_���王�_�Ɍ������x�N�g��
};

