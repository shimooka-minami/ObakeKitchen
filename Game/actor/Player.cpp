#include "stdafx.h"
#include "Player.h"
#include "actor/Player.h"
#include "actor/StateMachine.h"
#include "ActorTypes.h"


namespace
{
	struct AnimationData
	{
		const char* filename;
		bool loop;
	};
	AnimationData animationDataList[] =
	{
		AnimationData{"Assets/animData/ghost/idle.tka", true},
		AnimationData{"Assets/animData/ghost/walk.tka", true},
	};
	static_assert(ARRAYSIZE(animationDataList) == static_cast<uint8_t>(PlayerAnimationType::Num), "アニメーション数があっていません");
}


Player::Player()
{
	// ステータス生成
	m_status = new PlayerStatus();
	m_status->Setup();
	// ステートマシン生成
	m_stateMachine = std::make_unique<StateMachine>();
	m_stateMachine->Setup(this);
}


Player::~Player()
{
	delete m_status;
	m_status = nullptr;
}


bool Player::Start()
{
	// アニメーションクリップリストを生成
	m_animationClipList.resize(static_cast<uint8_t>(PlayerAnimationType::Num));
	for (int i = 0; i < static_cast<uint8_t>(PlayerAnimationType::Num); ++i) {
		auto* animationClip = new AnimationClip();
		animationClip->Load(animationDataList[i].filename);
		animationClip->SetLoopFlag(animationDataList[i].loop);
		m_animationClipList[i] = animationClip;
	}
	//プレイヤーモデル
	//m_modelRender.Init("Assets/modelData/player/GhostModel.tkm", *m_animationClipList.data(),enModelUpAxisZ);
	m_modelRender.Init("Assets/modelData/player/ghost.tkm",* m_animationClipList.data(), enModelUpAxisY);
	// キャラクターコントローラー生成
	m_characterController.Init(GetPlayerStatus()->GetRadius(), GetPlayerStatus()->GetHeight(), m_position);

	return true;
}


void Player::Update()
{
	//ステートマシンの更新を持ってくる
	m_stateMachine->Update();

	// ステートマシンから情報を取得
	m_position = m_stateMachine->GetPosition();
	m_scale    = m_stateMachine->GetScale();
	m_rotation = m_stateMachine->GetRotation();

	// @todo for 判定処理を後で入れる
	m_characterController.SetPosition(m_position);
	Vector3 moveSpeed = Vector3::Zero;
	m_characterController.Execute(moveSpeed, 0.0f);

	// キャラクター描画に情報を設定
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}


void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}