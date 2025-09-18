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

	// �����ڂ̂�
	m_modelRender.Init(modelName);
	// ���W���ݒ�
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
	// ���������蔻��̏�����
	m_characterController.Init(GetStatus()->GetRadius(), GetStatus()->GetHeight(), m_position);
	// ���̂ł͂Ȃ������蔻��̏�����
	m_collisionObject.CreateSphere(m_position, Quaternion::Identity, GetStatus()->GetRadius());

	return true;
}


void FoodPlate::Update()
{
	// �t���[�����Ԃ��擾
	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	// ���X�ɗ͂���߂�
	// TODO:���������̏����ɏC���\��
	m_addForce.Scale(0.8f);
	// ���������蔻������s
	m_position = m_characterController.Execute(m_addForce, deltaTime);
	// �����I�ł͂Ȃ������蔻��̍��W���X�V
	m_collisionObject.SetPosition(m_position);
	// ���f���̍��W���X�V����
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
		// ���łɗ͂�������Ă���ꍇ�͖���
		return;
	}

	const float addForcePower = GetStatus()->GetAddForcePower();
	m_addForce = direction * addForcePower;
}