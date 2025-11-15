/**
 * Collider.cpp
 * 当たり判定処理群
 */
#include "stdafx.h"
#include "Collider.h"


namespace app
{
    SphereCollider::SphereCollider()
    {
        m_shape = std::make_unique<SphereShape>();
    }


    SphereCollider::~SphereCollider()
    {
    }


    void SphereCollider::Update()
    {
        // 形状の座標を更新
        m_shape->SetPosition(m_position);
        // 半径更新
        GetShape<SphereShape>()->SetRadius(m_radius);
    }


    bool SphereCollider::IsHit(ICollider* other)
    {
        switch (other->GetShapeType())
        {
            // 球対球の当たり判定
            case enShapeType_Sphere:
            {
                const SphereShape* myShape = GetShape<SphereShape>();
                const SphereShape* otherShape = static_cast<const SphereShape*>(other->GetShape<SphereShape>());
                const float radiusSum = myShape->GetRadius() + otherShape->GetRadius();
                const float radiusSumSq = (radiusSum * radiusSum);
                const Vector3& myShapePosition = myShape->GetPosition();
				const Vector3& otherShapePosition = otherShape->GetPosition();
                const float distanceSqr = (myShapePosition - otherShapePosition).LengthSq();
                return distanceSqr <= radiusSumSq;
            }
        }
        // 未対応の形状
        K2_ASSERT(false, "未対応の当たり判定形状です");
        return false;
    }


    void SphereCollider::Create(const Vector3& position, const float radius)
    {
        m_position = position;
        m_radius = radius;
        Update();
    }
}