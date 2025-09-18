#pragma once

//�A�j���[�V�����N���b�v
enum EnPlayerAnimClip
{
	enPlayerAnimClip_Idle,
	enPlayerAnimClip_Walk,
	enPlayerAnimClip_Num,
};

class PlayerIState : public IGameObject
{
public:
	PlayerIState();
	~PlayerIState();

	bool Start() override;
	void Update() override;	
	void Render(RenderContext&rc) override;

	void PlayerMove(); //�ړ�
	void Dash(); //�_�b�V��
	void Have(); //����
	void Thorw(); //������
	void Cut(); //�؂�
	void Wash(); //��
	void Grill(); //�Ă�

private:
	AnimationClip m_animationClips[enPlayerAnimClip_Num]; //�v���C���[�A�j���[�V����

private:	//�ϐ�
	Vector3 m_moveSpeed; //�ړ����x
};

