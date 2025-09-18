#pragma once

//アニメーションクリップ
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

	void PlayerMove(); //移動
	void Dash(); //ダッシュ
	void Have(); //所持
	void Thorw(); //投げる
	void Cut(); //切る
	void Wash(); //洗う
	void Grill(); //焼く

private:
	AnimationClip m_animationClips[enPlayerAnimClip_Num]; //プレイヤーアニメーション

private:	//変数
	Vector3 m_moveSpeed; //移動速度
};

