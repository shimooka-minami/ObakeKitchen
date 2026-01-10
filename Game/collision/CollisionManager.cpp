#include "stdafx.h"
#include "CollisionManager.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"
#include "actor/Plate.h"

#include "gimmick/CoockingSpace.h"
#include "gimmick/FoodSpace.h"
#include "gimmick/PlateSpace.h"
#include "gimmick/DeliverySpace.h"

#include "score/Score.h"


CollisionHitManager* CollisionHitManager::m_instance = nullptr;


CollisionHitManager::CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


CollisionHitManager::~CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


void CollisionHitManager::Update()
{
	// ヒットするオブジェクトのペアを作る
	const uint32_t colSize = static_cast<uint32_t>(m_collisionInfoList.size());
	for (uint32_t i = 0; i < colSize; ++i) {
		for (uint32_t j = i + 1; j < colSize; ++j) {
			CollisionInfo* infoA = &m_collisionInfoList[i];
			CollisionInfo* infoB = &m_collisionInfoList[j];

			const bool isCheckA = infoA->m_collision->IsHit(infoB->m_collision.get());
			const bool isCheckB = infoB->m_collision->IsHit(infoA->m_collision.get());

			if (isCheckA || isCheckB)
			{
				// CollisionPairの中に同じ組み合わせがないかチェック
				bool exists = false;
				for (const auto& pair : m_collisionPairList) {
					if ((pair.m_left == infoA && pair.m_right == infoB) || (pair.m_left == infoB && pair.m_right == infoA)) {
						exists = true;
						break;
					}
				}
				// すでに登録済みではないなら追加する
				if (!exists) {
					m_collisionPairList.push_back(CollisionPair(infoA, infoB));
				}
			}
		}
	}

	// ヒットしたペアで衝突した時の処理をする
	// 今回のゲームではないがプレイヤーの攻撃がエネミーにあたったのでHPを減らすみたいなことをする
	for (auto& pair : m_collisionPairList) {

		// 納品スぺース用の処理
		if (UpdateHitDeliverySpace(pair)) {
			continue;
		}
		// 料理スペース用の処理
		if (UpdateHitCookingSpace(pair)) {
			continue;
		}
		// 食材スペース用の処理
		if (UpdateHitFoodSpace(pair)) {
			continue;
		}
		// 皿スペース用の処理
		if (UpdateHitPlateSpace(pair)) {
			continue;
		}
		//皿と食べ物の処理
		if (UpdateHitPlateAndFood(pair)) {
			continue;
		}
		// プレイヤーと食べ物の処理
		if (UpdateHitFoodPlate(pair)) {
			continue;
		}
		// プレイヤーと皿の処理
		if (UpdateHitPlate(pair)) {
			continue;
		}


	}

	m_collisionPairList.clear();
}


void CollisionHitManager::RegisterCollisionObject(EnCollisionType type, IGameObject* object, app::RefCollider collision)
{
	CollisionInfo info(type, object, collision);
	m_collisionInfoList.push_back(std::move(info));
}


void CollisionHitManager::UnregisterCollisionObject(IGameObject* object)
{
	for (auto it = m_collisionInfoList.begin(); it != m_collisionInfoList.end(); ++it)
	{
		if (it->m_object == object)
		{
			m_collisionInfoList.erase(it);
			break;
		}
	}
}


bool CollisionHitManager::UpdateHitCookingSpace(CollisionPair& pair)
{
	// 判定対象が料理スペースだった場合
	CoockingSpace* cookingSpace = GetTargetObject<CoockingSpace>(pair, enCollisionType_CookingSpace);
	Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);

	// 料理スペースじゃないなら処理しない
	if (cookingSpace == nullptr) {
		return false;
	}
	// playerじゃないなら処理しない
	if (player == nullptr) {
		return false;
	}

	// プレイヤーが近くにいることを知らせる
	cookingSpace->SetNearPlayer(true);

	// 料理スペースにプレイヤーが入ったときの処理
	player->GetStateMachine()->SetInCookingSpace(true);

	return true;
}


bool CollisionHitManager::UpdateHitFoodSpace(CollisionPair& pair)
{
	// 判定対象が料理スペースだった場合
	FoodSpace* foodSpace = GetTargetObject<FoodSpace>(pair, enCollisionType_FoodSpace);
	Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);

	// 料理スペースじゃないなら処理しない
	if (foodSpace == nullptr) {
		return false;
	}
	// playerじゃないなら処理しない
	if (player == nullptr) {
		return false;
	}

	if (player->GetStateMachine()->IsActionButtonA()) {
		// @tod ofor test
		float posX = rand() % 500;
		float posZ = rand() % 200;
		FoodPlate* foodPlate = NewGO<FoodPlate>(0, "foodPlate");
		foodPlate->Initialize(foodSpace->GetAssetPath().c_str(), foodSpace->GetCookedAssetsPath().c_str(), Vector3(posX, 0.0f, posZ), Vector3(1.0f, 1.0f, 1.0f), Quaternion::Identity);
	}
	return true;
}


bool CollisionHitManager::UpdateHitPlateSpace(CollisionPair& pair)
{
	// 判定対象が料理スペースだった場合
	PlateSpace* plateSpace = GetTargetObject<PlateSpace>(pair, enCollisionType_PlateSpace);
	Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);

	// 料理スペースじゃないなら処理しない
	if (plateSpace == nullptr) {
		return false;
	}
	// playerじゃないなら処理しない
	if (player == nullptr) {
		return false;
	}

	// プレイヤーが近くにいることを知らせる
	plateSpace->SetNearPlayer(true);

	if (player->GetStateMachine()->IsActionButtonA()) {

		// NOTE:例外でFindGO使う
		const auto& plateList = FindGOs<Plate>("plate");
		// 皿が4つあるなら皿を作らない
		if (plateList.size() >= 4) {
			return true;
		}

		// @todo for test
		float posX = rand() % 500;
		float posZ = rand() % 200;
		//FoodPlate* foodPlate = NewGO<FoodPlate>(0, "foodPlate");
		//foodPlate->Initialize(foodSpace->GetAssetPath().c_str(), foodSpace->GetCookedAssetsPath().c_str(), Vector3(posX, 0.0f, posZ), Vector3(1.0f, 1.0f, 1.0f), Quaternion::Identity);

		Plate* plate = NewGO<Plate>(0, "plate");
		plate->Initialize("Assets/modelData/Ground/plate.tkm", Vector3(posX, 0.0f, posZ), Vector3(1.0f, 1.0f, 1.0f), Quaternion::Identity);
	}
	return true;
}


bool CollisionHitManager::UpdateHitFoodPlate(CollisionPair& pair)
{
	Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);
	FoodPlate* foodPlate = GetTargetObject<FoodPlate>(pair, enCollisionType_Food);

	// プレイヤーが食材と当たってないとき
	if (foodPlate == nullptr)
	{
		return false;
	}
	if (player == nullptr)
	{
		return false;
	}

	// すでに皿に載っているなら、プレイヤーは直接

	//if (player->GetStateMachine()->IsActionButtonA()) {
	//	//食材が皿などの親を持っているかチェック
	//	if (foodPlate->m_transform.HasParent()) {
	//		//親子関係を解除(皿から引き離す)
	//		foodPlate->m_transform.ClearParent();
	//	}
	//}

	// プレイヤーの前に皿がない場合
	if (!player->GetStateMachine()->IsForwardFood())
	{
		if (foodPlate->m_transform.HasParent()) {
			return false;
		}

		// 近くにある（プレイヤーと皿が接触しているときの処理）
		player->GetStateMachine()->SetNearFood(true);

		Vector3 playerDirection = player->GetStateMachine()->GetDirection();
		Vector3 foodDirection = foodPlate->m_transform.m_position - player->m_transform.m_position;
		foodDirection.Normalize();

		// 内積を入れる変数
		float dot;
		// 内積の計算 プレイヤーからフードの方向
		dot = playerDirection.Dot(foodDirection);
		// 内積からacosで角度(円周率)を求めている
		float angle = acos(dot);

		// 円周率を角度に変換したとき、プレイヤーとフードの角度が30度以上なら
		player->GetStateMachine()->SetForwardFood(angle <= Math::DegToRad(30.0f));

		// フードクラスをターゲットに設定
		player->GetStateMachine()->SetTargetFood(foodPlate);
	}

	return true;
}

bool CollisionHitManager::UpdateHitPlateAndFood(CollisionPair& pair)
{
	// ペアからPlateとFoodPlateを取得
	Plate* plate = GetTargetObject<Plate>(pair, enCollisionType_Plate);
	FoodPlate* food = GetTargetObject<FoodPlate>(pair, enCollisionType_Food);

	// 両方が揃っていないなら終了
	if (plate == nullptr
		|| food == nullptr) {
		return false;
	}

	//ここまで来たら当たったということ
	OutputDebugStringA("皿と食材が衝突しました！！\n");

	// そのさらに既に何かが載っているなら、新しい料理は載せない
	if (plate->IsFull()) {
		return false;
	}

	// 自分自身同士の衝突なら無視
	if ((void*)plate == (void*)food) {
		return false;
	}

	// 食べ物がすでに何かに載っていないかチェック
	if (food->m_transform.HasParent()) {
		return false;
	}

	// 皿に食べ物を載せる
	plate->AttachFood(food);

	return true;
}


bool CollisionHitManager::UpdateHitPlate(CollisionPair& pair)
{
	Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);
	Plate* plate = GetTargetObject<Plate>(pair, enCollisionType_Plate);

	// プレイヤーが食材と当たってないとき
	if (plate == nullptr)
	{
		return false;
	}
	if (player == nullptr)
	{
		return false;
	}

	// プレイヤーの前に皿がない場合
	if (!player->GetStateMachine()->IsForwardPlate())
	{
		if (plate->m_transform.HasParent()) {
			return false;
		}

		// 近くにある（プレイヤーと皿が接触しているときの処理）
		player->GetStateMachine()->SetNearPlate(true);

		Vector3 playerDirection = player->GetStateMachine()->GetDirection();
		Vector3 plateDirection = plate->m_transform.m_position - player->m_transform.m_position;
		plateDirection.Normalize();

		// 内積を入れる変数
		float dot;
		// 内積の計算 プレイヤーから皿の方向
		dot = playerDirection.Dot(plateDirection);
		// 内積からacosで角度(円周率)を求めている
		float angle = acos(dot);

		// 円周率を角度に変換したとき、プレイヤーと皿の角度が30度以上なら
		player->GetStateMachine()->SetForwardPlate(angle <= Math::DegToRad(30.0f));

		// フードクラスをターゲットに設定
		player->GetStateMachine()->SetTargetPlate(plate);
	}

	return true;
}



bool CollisionHitManager::UpdateHitDeliverySpace(CollisionPair& pair)
{
	Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);
	DeliverySpace* deliverySpace = GetTargetObject<DeliverySpace>(pair, enCollisionType_DeliverySpace);

	// プレイヤーが納品場と当たってないとき
	if (deliverySpace == nullptr)
	{
		return false;
	}
	if (player == nullptr)
	{
		return false;
	}

	// プレイヤーが近くにいることを知らせる
	deliverySpace->SetNearPlayer(true);

	// 取得
	FoodPlate* targetFood = player->GetStateMachine()->GetTargetFood();
	if (targetFood == nullptr)
	{
		return false;
	}
	if (targetFood->IsCoocked())
	{
		// 親子関係終わり
		targetFood->m_transform.ClearParent();
		player->m_transform.ClearChild();
		// 持ち物じゃない
		player->GetStateMachine()->SetTargetFood(nullptr);
		player->GetStateMachine()->SetForwardFood(false);
		player->GetStateMachine()->SetNearFood(false);
		// スコア処理
		DeleteGO(targetFood);
		// スコアの加算
		Score::GetInstance()->AddScore(50);
		return true;
	}

	return false;
}
