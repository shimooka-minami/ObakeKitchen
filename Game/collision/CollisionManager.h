/**
 * CollisionManager.h
 * 当たり判定管理
 */
#pragma once
#include "Collider.h"


class Player;
class FoodPlate;


enum EnCollisionType
{
	enCollisionType_Player,
	enCollisionType_FoodPlate,
	enCollisionType_CookingSpace,	// 料理スペース
	enCollisionType_FoodSpace,		// 食材スペース
	enCollisionType_DeliverySpace,	// 納品スペース
};




struct CollisionInfo
{
	EnCollisionType m_type;	// 当たり判定の種類(プレイヤーと食材がヒットしたみたいな処理をするために必要。自分がだれかの判断)
	IGameObject* m_object;	// 当たり判定を持つオブジェクトのポインタ
	app::RefCollider m_collision; // 当たり判定のコライダー
	//
	CollisionInfo() : m_type(enCollisionType_Player), m_object(nullptr), m_collision(nullptr) {}
	CollisionInfo(const EnCollisionType type, IGameObject* object, app::RefCollider collision) : m_type(type), m_object(object), m_collision(collision) {}
};




struct CollisionPair
{
	CollisionInfo* m_left;	// 当たり判定A
	CollisionInfo* m_right;	// 当たり判定B
	//
	CollisionPair() : m_left(nullptr), m_right(nullptr) {}
	CollisionPair(CollisionInfo* left, CollisionInfo* right) : m_left(left), m_right(right) {}
};




/**
 * 当たり判定処理を一括で行うクラス
 * NOTE:シングルトンでインスタンスを一つにしてアクセスポイントを提供する
 */
class CollisionHitManager
{
private:
	/** 当たり判定オブジェクトのリスト */
	std::vector<CollisionInfo> m_collisionInfoList;
	/** 当たり判定のペア */
	std::vector<CollisionPair> m_collisionPairList;


private:
	CollisionHitManager();
	~CollisionHitManager();


public:
	void Update();


public:
	/** 判定処理をしたいオブジェクトを登録 */
	void RegisterCollisionObject(EnCollisionType type, IGameObject* object, app::RefCollider collision);
	void UnregisterCollisionObject(IGameObject* object);


private:
	bool UpdateHitCookingSpace(CollisionPair& pair);
	bool UpdateHitFoodSpace(CollisionPair& pair);
	bool UpdateHitFoodPlate(CollisionPair& pair);
	bool UpdateHitDeliverySpace(CollisionPair& pair);


private:
	/**
	 * 指定したクラスを取得する
	 * NOTE: 指定したクラスが存在しない場合はnullptrを返す
	 */
	template <typename T>
	T* GetTargetObject(CollisionPair& pair, const EnCollisionType targetType)
	{
		if (pair.m_left->m_type == targetType)
		{
			return static_cast<T*>(pair.m_left->m_object);
		}
		else if (pair.m_right->m_type == targetType)
		{
			return static_cast<T*>(pair.m_right->m_object);
		}
		return nullptr;
	}


private:
	static CollisionHitManager* m_instance;


public:
	static void Create()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CollisionHitManager();
		}
	}
	static CollisionHitManager& Get()
	{
		return *m_instance;
	}
	static void Delete()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};