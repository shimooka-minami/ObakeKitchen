/**
 * Collider.h
 * 当たり判定処理群
 */
#pragma once
#include "Shape.h"


namespace app
{
	/** 形状を持つ当たり判定処理の基底クラス */
	class ICollider
	{
	protected:
		/** 形状(各継承先で好きな形にする) */
		std::unique_ptr<IShape> m_shape;
		/** 座標 */
		Vector3 m_position = Vector3::Zero;


	public:
		ICollider() {}
		virtual ~ICollider() {}

		/** 更新(座標更新など行う) */
		virtual void Update() = 0;
		/** 当たり判定処理 */
		virtual bool IsHit(ICollider* other) = 0;

		/** 座標取得 */
		const Vector3& GetPosition() const { return m_position; }
		/** 座標設定 */
		void SetPosition(const Vector3& position) { m_position = position; }


	public:
		/** 形状の種類取得 */
		EnShapeType GetShapeType() const { return m_shape->GetShapeType(); }

		/** 指定した形状取得 */
		template<typename TShape>
		TShape* GetShape() { return dynamic_cast<TShape*>(m_shape.get()); }
	};
	/** これを使う！！ */
	using RefCollider = std::shared_ptr<ICollider>;



	/** 球コリジョン */
	class SphereCollider : public ICollider
	{
	private:
		/** 半径 */
		float m_radius = 1.0f;


	public:
		SphereCollider();
		~SphereCollider();

		/** 更新処理 */
		void Update() override;
		/** 当たり判定処理 */
		bool IsHit(ICollider* other) override;

		/** 形状生成 */
		void Create(const Vector3& position, const float radius);

		/** 半径取得 */
		float GetRadius() const { return m_radius; }
		/** 半径設定 */
		void SetRadius(const float radius) { m_radius = radius; }
	};
	/** これを使う！！ */
	using RefSphereCollider = std::shared_ptr<SphereCollider>;
	static RefSphereCollider CreateSphereCollider(const Vector3& position, const float radius)
	{
		auto collider = std::make_shared<SphereCollider>();
		collider->Create(position, radius);
		return collider;
	}
}