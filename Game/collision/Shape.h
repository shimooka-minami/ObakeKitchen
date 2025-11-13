/**
 * Shape.h
 * 形状
 */
#pragma once


/** コリジョン処理専用予定：外から触らない */
namespace imp
{
	/**
	 * 回転など考慮されないBoxの判定
	 */
	class AABB
	{
	private:
		Vector3 m_min;
		Vector3 m_max;


	public:
		AABB() {}
		~AABB() {}

		void Set(const Vector3 min, const Vector3 max)
		{
			m_max = max;
			m_min = min;
		}
		void Set(const Vector3 center, const float halfSize)
		{
			// min
			m_min.x = center.x - halfSize;
			m_min.y = center.y - halfSize;
			m_min.z = center.z - halfSize;
			// max
			m_max.x = center.x + halfSize;
			m_max.y = center.y + halfSize;
			m_max.z = center.z + halfSize;
		}

		/** 内包されている */
		bool IsContains(const AABB other)
		{
			// 最小値よりも相手の最大値が小さい場合は当たっていない
			if (m_min.x > other.m_max.x) return false;
			if (m_min.y > other.m_max.y) return false;
			if (m_min.z > other.m_max.z) return false;

			// 最大値よりも相手の最小値が大きい場合は当たってない
			if (m_max.x < other.m_min.x) return false;
			if (m_max.y < other.m_min.y) return false;
			if (m_max.z < other.m_min.z) return false;

			return true;
		}
	};
}


/** 形状の種類 */
enum EnShapeType
{
	enShapeType_Sphere,
	enShapeType_Box,
	enShapeType_None,
};



/************************************/




/**
 * 形状のインターフェース
 */
class IShape : public Noncopyable
{
private:
	/** 形状の種類 */
	EnShapeType m_shapeType;

	/** 座標 */
	Vector3 m_position;
	/** NOTE: 回転、拡縮には未対応 */

public:
	IShape(const EnShapeType shapeType) : m_shapeType(shapeType) {}
	virtual ~IShape() {}


public:
	void SetPosition(const Vector3& position) { m_position = position; }
	const Vector3& GetPosition() const { return m_position; }

	EnShapeType GetShapeType() const { return m_shapeType; }
};




/************************************/


/**
 * 球の形状
 */
class SphereShape : public IShape
{
private:
	float m_radius = 0.0f;

public:
	SphereShape();
	~SphereShape();


public:
	/** 半径設定 */
	void SetRadius(const float radius) { m_radius = radius; }
	float GetRadius() const { return m_radius; }
};




/************************************/


class BoxShape : public IShape
{
private:
	imp::AABB m_aabb;


public:
	BoxShape();
	~BoxShape();
};