/**
 * CollisionManager.h
 * 当たり判定管理
 */
#pragma once


class Player;
class FoodPlate;



/**
 * 当たり判定処理を一括で行うクラス
 * NOTE:シングルトンでインスタンスを一つにしてアクセスポイントを提供する
 */
class CollisionHitManager
{
private:
	// @todo for test
	// 仮の処理
	Player* m_player = nullptr;
	FoodPlate* m_foodPlate = nullptr;
	// ここまで仮

private:
	CollisionHitManager() {}
	~CollisionHitManager() {}


public:
	void Update();


	// @todo for test
	// 仮の処理
public:
	void SetPlayer(Player* player) { m_player = player; }
	void SetFoodPlate(FoodPlate* foodPlate) { m_foodPlate = foodPlate; }
	//ここまで仮


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