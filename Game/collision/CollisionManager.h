/**
 * CollisionManager.h
 * 当たり判定管理
 */
#pragma once


class Player;
class FoodPlate;




enum EnCollisionType
{
	enCollisionType_Player,
	enCollisionType_FoodPlate,
};




struct CollisionInfo
{
	EnCollisionType m_type;	// 当たり判定の種類(プレイヤーと食材がヒットしたみたいな処理をするために必要。自分がだれかの判断)
	IGameObject* m_object;	// 当たり判定を持つオブジェクトのポインタ
	CollisionObject* m_collision; // 当たり判定オブジェクトのポインタ
	//
	CollisionInfo() : m_type(enCollisionType_Player), m_object(nullptr), m_collision(nullptr) {}
	CollisionInfo(const EnCollisionType type, IGameObject* object, CollisionObject* collision) : m_type(type), m_object(object), m_collision(collision) {}
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


	// @todo for test
	// 仮の処理
	Player* m_player = nullptr;
	FoodPlate* m_foodPlate = nullptr;
	// ここまで仮

private:
	CollisionHitManager();
	~CollisionHitManager();


public:
	void Update();


	// @todo for test
	// 仮の処理
public:
	void SetPlayer(Player* player) { m_player = player; }
	void SetFoodPlate(FoodPlate* foodPlate) { m_foodPlate = foodPlate; }
	//ここまで仮

	/** 判定処理をしたいオブジェクトを登録 */
	void RegisterCollisionObject(EnCollisionType type, IGameObject* object, CollisionObject* collision);
	void UnregisterCollisionObject(IGameObject* object);


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