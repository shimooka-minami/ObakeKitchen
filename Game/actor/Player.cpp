#include "stdafx.h"
#include "Player.h"
#include "actor/StateMachine.h"
#include "ActorTypes.h"
#include "collision/CollisionManager.h"


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
	m_characterController.Init(GetPlayerStatus()->GetRadius(), GetPlayerStatus()->GetHeight(), m_transform.m_position);
	// 物理的ではない判定を生成
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, GetPlayerStatus()->GetRadius(), enCollisionType_Player);

	return true;
}


void Player::Update()
{
	//ステートマシンの更新を持ってくる
	m_stateMachine->Update();

	// 判定処理をする
	Vector3 move = m_stateMachine->GetMoveVector();
	const Vector3& position = m_characterController.Execute(move, 1.0f);	// あえて1.0f
	
	// 判定処理結果の座標を設定
	m_transform.m_localPosition = position;
	m_transform.m_localRotation.SetRotationYFromDirectionXZ(move);	// プレイヤーが移動している方向
	m_transform.UpdateTransform();

	// ステートマシンに座標設定
	m_stateMachine->SetPosition(m_transform.m_position);
	// ゴーストの判定に座標設定
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
	// キャラクター描画に情報を設定
	m_modelRender.SetPosition(m_transform.m_position);
	m_modelRender.SetRotation(m_transform.m_rotation);
	m_modelRender.SetScale(m_transform.m_scale);
	m_modelRender.Update();
}


void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}