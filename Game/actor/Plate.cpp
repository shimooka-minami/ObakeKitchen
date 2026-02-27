#include "stdafx.h"
#include "Plate.h"
#include "collision/GhostBody.h"
#include "collision/CollisionManager.h"


Plate::Plate()
{
	m_status = CreateStatus<FoodStatus>();
}


Plate::~Plate()
{

}

bool Plate::Start()
{
	// 物理当たり判定の初期化
	m_characterController.Init(GetStatus()->GetRadius(), GetStatus()->GetHeight(), m_transform.m_position, enCollisionAttr_Plate);
	// 物体ではない当たり判定の初期化
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, GetStatus()->GetRadius(), enCollisionType_Plate);

	CollisionHitManager::Get().RegisterCollisionObject(enCollisionType_Plate, this, m_ghostBody->GetCollider());

	m_status = CreateStatus<FoodStatus>();


	return true;
}


void Plate::Update()
{
	// フレーム時間を取得
	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	// 物理当たり判定を実行
	if (!m_transform.HasParent()) {
		Vector3 addForce = Vector3::Zero;
		addForce.y -= 100.0f;
		m_transform.m_localPosition = m_characterController.Execute(addForce, deltaTime);
	}
	// 座標を更新
	m_transform.UpdateTransform();
	// 物理的ではない当たり判定の座標を更新
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
	// モデルの座標を更新する
	m_modelRender.SetPosition(m_transform.m_position);
	m_modelRender.Update();

	m_isNearPlayer = false;
}


void Plate::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


void Plate::Initialize(const char* modelName, const Vector3& position, const Vector3 scale, const Quaternion& rotation)
{
	m_transform.m_localPosition = position;
	m_transform.m_localScale = scale;
	m_transform.m_localRotation = rotation;

	// 座標更新
	m_transform.UpdateTransform();

	// 見た目のみ
	m_modelRender.Init(modelName);
	// 座標等設定
	m_modelRender.SetTRS(position, rotation, scale);
	m_modelRender.Update();
}


void Plate::SetPosition(const Vector3& position)
{
	m_transform.m_localPosition = position;
	m_transform.UpdateTransform();
	m_characterController.SetPosition(m_transform.m_position);
	m_ghostBody->SetPosition(m_transform.m_position);
}


void Plate::Put(const Vector3& direction)
{
	//if (m_addForce.LengthSq() >= 0.01f) {
	//	// すでに力が加わっている場合は無視
	//	return;
	//}

	//const float addForcePower = GetStatus()->GetAddForcePower();
	//m_addForce = direction * addForcePower;
}

void Plate::AttachFood(FoodPlate* food)
{
	////すでに親がいるなら載せない
	//if (food->m_transform.HasParent()) {
	//	return;
	//}

	// 親子関係を結ぶ
	food->m_transform.SetParent(&m_transform);

	// 親の中心から見て、少し上に配置
	food->m_transform.m_localPosition = Vector3(0.0f, 15.0f, 0.0f);

	// 料理側の当たり判定を一時的に削除
	CollisionHitManager::Get().UnregisterCollisionObject(food);

	// 座標変更を即座に反映
	food->m_transform.UpdateTransform();
}




/**********************************/


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
	//読んでしまうとPlateの判定が作られるので共通の変数初期化だけを行い、判定作成はFoodPlate独自で行う
	//SuperClass::Start();

	// 物理当たり判定の初期化
	m_characterController.Init(GetStatus()->GetRadius(), GetStatus()->GetHeight(), m_transform.m_position, enCollsiionAttr_Food);
	// 物体ではない当たり判定の初期化
	m_ghostBody = std::make_unique<SphereGhostBody>();
	m_ghostBody->Create(this, m_transform.m_position, GetStatus()->GetRadius() * 5.0f, enCollisionType_Food);  // ちょっと大きくしてみた

	CollisionHitManager::Get().RegisterCollisionObject(enCollisionType_Food, this, m_ghostBody->GetCollider());
	return true;
}


void FoodPlate::Update()
{
	// フレーム時間を取得
	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	// 徐々に力を弱める
	// TODO:いい感じの処理に修正予定
	m_addForce.Scale(0.9f);
	// 物理当たり判定を実行
	if (!m_transform.HasParent()) {
		m_addForce.y -= 100.0f;
		m_transform.m_localPosition = m_characterController.Execute(m_addForce, deltaTime);
	}
	// 座標を更新
	m_transform.UpdateTransform();
	// 物理的ではない当たり判定の座標を更新
	m_ghostBody->SetPosition(m_transform.m_position);
	m_ghostBody->Update();
	// モデルの座標を更新する
	if (m_state == enState_Coocked) {
		m_coockedRender.SetPosition(m_transform.m_position);
		m_coockedRender.Update();
	}
	else {
		m_modelRender.SetPosition(m_transform.m_position);
		m_modelRender.Update();
	}
}


void FoodPlate::Render(RenderContext& rc)
{
	if (m_state == enState_Coocked) {
		m_coockedRender.Draw(rc);
	}
	else {
		m_modelRender.Draw(rc);
	}
}


void FoodPlate::Initialize(const char* modelName, const char* coockedModelName, const Vector3& position, const Vector3 scale, const Quaternion& rotation)
{
	m_transform.m_localPosition = position;
	m_transform.m_localScale = scale;
	m_transform.m_localRotation = rotation;

	// 座標更新
	m_transform.UpdateTransform();

	// 見た目のみ
	m_modelRender.Init(modelName);
	// 座標等設定
	m_modelRender.SetTRS(position, rotation, scale);
	m_modelRender.Update();

	m_coockedRender.Init(coockedModelName);
}


void FoodPlate::SetPosition(const Vector3& position)
{
	m_transform.m_localPosition = position;
	m_transform.UpdateTransform();
	m_characterController.SetPosition(m_transform.m_position);
	m_ghostBody->SetPosition(m_transform.m_position);
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