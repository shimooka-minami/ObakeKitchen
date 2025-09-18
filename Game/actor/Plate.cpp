#include "stdafx.h"
#include "Plate.h"


bool Plate::Start()
{
	return true;
}


void Plate::Update()
{
}


void Plate::Render(RenderContext& rc)
{
}


void Plate::Initialize(const char* modelName, const Vector3& position, const Vector3 scale, const Quaternion& rotation)
{
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;

	// 見た目のみ
	m_modelRender.Init(modelName);
	// 座標等設定
	m_modelRender.SetTRS(position, rotation, scale);
	m_modelRender.Update();
}





FoodPlate::FoodPlate()
{
	m_status = CreateStatus<FoodStatus>();
}


FoodPlate::~FoodPlate()
{
	if (m_status) {
		delete m_status;
		m_status = nullptr;
	}
}


bool FoodPlate::Start()
{
	// 物理当たり判定の初期化
	m_characterController.Init(GetStatus()->GetRadius(), GetStatus()->GetHeight(), m_position);
	// 物体ではない当たり判定の初期化
	m_collisionObject.CreateSphere(m_position, Quaternion::Identity, GetStatus()->GetRadius());

	return true;
}


void FoodPlate::Update()
{
	// フレーム時間を取得
	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	// 徐々に力を弱める
	// TODO:いい感じの処理に修正予定
	m_addForce.Scale(0.8f);
	// 物理当たり判定を実行
	m_position = m_characterController.Execute(m_addForce, deltaTime);
	// 物理的ではない当たり判定の座標を更新
	m_collisionObject.SetPosition(m_position);
	// モデルの座標を更新する
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}


void FoodPlate::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


void FoodPlate::Throw(const Vector3& direction)
{
	if (m_addForce.LengthSq() >= 0.01f) {
		// すでに力が加わっている場合は無視
		return;
	}

	const float addForcePower = GetStatus()->GetAddForcePower();
	m_addForce = direction * addForcePower;
}