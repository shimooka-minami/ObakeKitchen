#include "stdafx.h"
#include "NPCController.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"
#include "actor/Plate.h"
#include "gimmick/CoockingSpace.h"
#include "gimmick/DeliverySpace.h"



/** 名前被り等の衝突を防ぐため */
namespace
{
    // @todo for test
    constexpr float PLAYER_MOVE_SPEED = 3.0f; // 移動速度


    // @todo for test
    enum EnAIType
    {
        enAIType_Support,   // 協力型(強いAI)
        enAIType_Weak,      // 邪魔型(弱いAI)
    };

    static EnAIType sAiType = enAIType_Support;
}


// Static変数の初期化
std::map<NPCController::EnAIStateID, NPCController::AIState> NPCController::m_stateMap;


NPCController::NPCController()
{
}


NPCController::~NPCController()
{
}


bool NPCController::Start()
{
    return true;
}


void NPCController::Update()
{
    auto* currentState = FindAIState(m_currentState);
    if (currentState == nullptr) {
        K2_ASSERT(false, "対象の処理が見つかりません\n");
        return;
    }

    // 初回起動時のEnter処理
    if (!m_isInitialized) {
        currentState->enter(this);
        m_isInitialized = true;
    }

    // A. 遷移判定 (CheckTransition)
    // 次のステートIDを取得する（-1なら遷移なし）
    const int nextState = currentState->check(this);
    // B. 遷移が必要な場合の処理
    if (nextState != -1 && nextState != m_currentState) {
        ChangeState((EnAIStateID)nextState);
        currentState = FindAIState(m_currentState);
    }

    // 現在のステートのメイン処理 (Update)
    currentState->update(this);

    prePosition = m_target->m_transform.m_position;
}


void NPCController::Render(RenderContext& rc)
{

}


void NPCController::ChangeState(EnAIStateID nextState)
{
    // 指定したnextStateがおかしい
    if (nextState < enAIState_Invalid || nextState >= enAIState_Max) {
        return;
    }

    auto* currentState = FindAIState(m_currentState);
    // 現在のステートのExitを呼ぶ
    currentState->exit(this);
    // ステート更新
    m_currentState = nextState;
    // 新しいステートのEnterを呼ぶ
    currentState = FindAIState(m_currentState);
    currentState->enter(this);
}




// -----------------------------------------------------
//  各ステートの実装 (static関数)
// -----------------------------------------------------


void NPCController::Initialize()
{
    // 待機
    RegisterState(enAIState_Idle, EnterIdle, UpdateIdle, ExitIdle, CheckIdle);
    // 適当に移動
    RegisterState(enAIState_FreeMove, EnterFreeMove, UpdateFreeMove, ExitFreeMove, CheckFreeMove);
    // 探索
    RegisterState(enAIState_Search, EnterSearch, UpdateSearch, ExitSearch, CheckSearch);
    // 対象の食べ物へ移動
    RegisterState(enAIState_TargetFoodMove, EnterTargetFoodMove, UpdateTargetFoodMove, ExitTargetFoodMove, CheckTargetFoodMove);
    // 食べ物を拾う
    RegisterState(enAIState_PickupFood, EnterPickupFood, UpdatePickupFood, ExitPickupFood, CheckPickupFood);
    // 料理場へ移動
    RegisterState(enAIState_CoockingSpaceMove, EnterCoockingSpaceMove, UpdateCoockingSpaceMove, ExitCoockingSpaceMove, CheckCoockingSpaceMove);
    // 納品場へ移動
    RegisterState(enAIState_DeliverySpaceMove, EnterDeliverySpaceMove, UpdateDeliverySpaceMove, ExitDeliverySpaceMove, CheckDeliverySpaceMove);
    // 料理する
    RegisterState(enAIState_Coocking, EnterCoocking, UpdateCoocking, ExitCoocking, CheckCoocking);
}




void NPCController::EnterSearch(NPCController* npc)
{
    npc->m_targetPosition = Vector3::Zero;

    // TODO: 例外でFindGO使用
    const auto& foodPlateList = FindGOs<FoodPlate>("foodPlate");
    // 対象の食べ物をみつける
    Vector3 targetPosition = Vector3::Zero;
    float targetDistance = FLT_MAX;
    for (auto* foodPlate : foodPlateList) {
        Vector3 vec = foodPlate->m_transform.m_position - npc->m_target->m_transform.m_position;
        const float distance = vec.Length();
        if (distance < targetDistance) {
            targetPosition = foodPlate->m_transform.m_position;
            targetDistance = distance;
            npc->isFind = true;
        }
    }
    npc->m_targetPosition = targetPosition;
}


void NPCController::UpdateSearch(NPCController* npc)
{

}


void NPCController::ExitSearch(NPCController* npc)
{
}


int NPCController::CheckSearch(NPCController* npc)
{
    if (npc->isFind) {
        return enAIState_TargetFoodMove;
    }
    return enAIState_FreeMove;
}




void NPCController::EnterIdle(NPCController* npc)
{
    npc->m_elapsedTime = 0.0f;
}


void NPCController::UpdateIdle(NPCController* npc)
{
    npc->m_elapsedTime += g_gameTime->GetFrameDeltaTime();
}


void NPCController::ExitIdle(NPCController* npc)
{
}


int NPCController::CheckIdle(NPCController* npc)
{
    const float idleTime = static_cast<float>(rand() % 500) * 0.01f;
    if (npc->m_elapsedTime > idleTime) {
        // 半分の確率で適当に移動する
        if (rand() % 10 >= 5) {
            return enAIState_FreeMove;
        }
        return enAIState_Search;
    }
    return enAIState_Invalid;
}




void NPCController::EnterFreeMove(NPCController* npc)
{
    bool isXReverce = rand() % 2 >= 1 ? true : false;
    bool isZReverce = rand() % 2 >= 1 ? true : false;
    npc->m_targetPosition = Vector3(rand() % 300 * (isXReverce ? 1.0f : -1.0f), 0.0f, rand() % 300 * (isZReverce ? 1.0f : -1.0f));
}


void NPCController::UpdateFreeMove(NPCController* npc)
{
    // 対象座標までの距離
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    // 方向
    Vector3 direction = distance;
    direction.Normalize();

    npc->m_target->GetStateMachine()->SetDirection(direction);
    npc->m_target->GetStateMachine()->SetStickLAmount(1.0f);
}


void NPCController::ExitFreeMove(NPCController* npc)
{
    npc->m_target->GetStateMachine()->SetStickLAmount(0.0f);
}


int NPCController::CheckFreeMove(NPCController* npc)
{
    // 対象座標までの距離
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    const float radius = npc->m_target->GetPlayerStatus()->GetRadius();
    if (distance.Length() <= radius) {
        return enAIState_Idle;
    }
    return enAIState_Invalid;
}




void NPCController::EnterTargetFoodMove(NPCController* npc)
{
}


void NPCController::UpdateTargetFoodMove(NPCController* npc)
{
    // 対象座標までの距離
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    // 方向
    Vector3 direction = distance;
    direction.y = 0.0f;
    direction.Normalize();
    // 移動
    npc->m_target->GetStateMachine()->SetDirection(direction);
    npc->m_target->GetStateMachine()->SetStickLAmount(1.0f);
}


void NPCController::ExitTargetFoodMove(NPCController* npc)
{
    // 対象座標初期化
    npc->m_targetPosition = Vector3::Zero;
}


int NPCController::CheckTargetFoodMove(NPCController* npc)
{
    Vector3 vec = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    vec.y = 0.0f;
    float distance = vec.Length();
    // 一定の距離(TODO:この数値を別のところからとってくるようにする)
    if (distance < 10.0f) {
        return enAIState_PickupFood;
    }

    // 前回の位置と変わっていないなら適当に移動させる
    {
        Vector3 v = vec - npc->m_target->m_transform.m_position;
        if (v.Length() < 0.1f) {
            return enAIState_PickupFood;
        }
    }

    // 現状維持
    return enAIState_Invalid;
}




void NPCController::EnterPickupFood(NPCController* npc)
{
    npc->m_elapsedTime = 0.0f;
}


void NPCController::UpdatePickupFood(NPCController* npc)
{
    // 近くに食べ物があるはずなのでAボタンを押す
    npc->m_target->GetStateMachine()->ActionButtonA(true);

    // 念のため数秒たったら、この状態を解除するため経過時間を数える
    npc->m_elapsedTime += g_gameTime->GetFrameDeltaTime();
}


void NPCController::ExitPickupFood(NPCController* npc)
{
    // 押すのをやめる
    npc->m_target->GetStateMachine()->ActionButtonA(false);
}


int NPCController::CheckPickupFood(NPCController* npc)
{
    // 食べ物が取れているなら
    auto* targetFood = npc->m_target->GetStateMachine()->GetTargetFood();
    if (targetFood) {
        if (targetFood->IsCoocked()) {
            return enAIState_DeliverySpaceMove;
        }
        return enAIState_CoockingSpaceMove;
    }

    // 2秒ほど続けてみる
    if (npc->m_elapsedTime > 2.0f) {
        // ２秒つづけて取れなかったら適当に移動させる
        return enAIState_FreeMove;
    }
    return enAIState_Invalid;
}




void NPCController::EnterCoockingSpaceMove(NPCController* npc)
{
    // TODO:例外でFindGO使用
    const auto& coockingSpaceList = FindGOs<CoockingSpace>("coockingSpace");
    float targetDisatance = FLT_MAX;
    // 近い料理場を探す
    for (auto* coockingSpace : coockingSpaceList) {
        Vector3 vec = coockingSpace->m_transform.m_position - npc->m_target->m_transform.m_position;
        float distance = vec.Length();
        if (distance < targetDisatance) {
            npc->m_targetPosition = coockingSpace->m_transform.m_position;
            distance = targetDisatance;
        }
    }
}


void NPCController::UpdateCoockingSpaceMove(NPCController* npc)
{
    // 対象座標までの距離
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    // 方向
    Vector3 direction = distance;
    direction.y = 0.0f;
    direction.Normalize();
    // 移動
    npc->m_target->GetStateMachine()->SetDirection(direction);
    npc->m_target->GetStateMachine()->SetStickLAmount(1.0f);
}


void NPCController::ExitCoockingSpaceMove(NPCController* npc)
{
    npc->m_targetPosition = Vector3::Zero;
}


int NPCController::CheckCoockingSpaceMove(NPCController* npc)
{
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    if (distance.Length() < 60.0f) {
        return enAIState_Coocking;
    }
    return enAIState_Invalid;
}




void NPCController::EnterCoocking(NPCController* npc)
{
    npc->m_elapsedTime = 0.0f;
}


void NPCController::UpdateCoocking(NPCController* npc)
{
    // 近くに料理場があるはずなのでAボタンを押す
    npc->m_target->GetStateMachine()->ActionButtonA(true);

    // 念のため数秒たったら、この状態を解除するため経過時間を数える
    npc->m_elapsedTime += g_gameTime->GetFrameDeltaTime();
}


void NPCController::ExitCoocking(NPCController* npc)
{
    // 押すのをやめる
    npc->m_target->GetStateMachine()->ActionButtonA(false);
}


int NPCController::CheckCoocking(NPCController* npc)
{
    // 食べ物が取れているなら
    auto* targetFood = npc->m_target->GetStateMachine()->GetTargetFood();
    if (targetFood) {
        if (targetFood->IsCoocked()) {
            return enAIState_DeliverySpaceMove;
        }
    }

    if (npc->m_elapsedTime > 2.0f) {
        return enAIState_FreeMove;
    }

    return enAIState_Invalid;
}




void NPCController::EnterDeliverySpaceMove(NPCController* npc)
{
    // TODO:例外でFindGO使用
    const auto& spaceList = FindGOs<DeliverySpace>("deliverySpace");
    float targetDisatance = FLT_MAX;
    // 近い料理場を探す
    for (auto* space : spaceList) {
        Vector3 vec = space->m_transform.m_position - npc->m_target->m_transform.m_position;
        float distance = vec.Length();
        if (distance < targetDisatance) {
            npc->m_targetPosition = space->m_transform.m_position;
            distance = targetDisatance;
        }
    }
}


void NPCController::UpdateDeliverySpaceMove(NPCController* npc)
{
    // 対象座標までの距離
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    // 方向
    Vector3 direction = distance;
    direction.y = 0.0f;
    direction.Normalize();
    // 移動
    npc->m_target->GetStateMachine()->SetDirection(direction);
    npc->m_target->GetStateMachine()->SetStickLAmount(1.0f);
}


void NPCController::ExitDeliverySpaceMove(NPCController* npc)
{
    npc->m_targetPosition = Vector3::Zero;
}


int NPCController::CheckDeliverySpaceMove(NPCController* npc)
{
    Vector3 distance = npc->m_targetPosition - npc->m_target->m_transform.m_position;
    if (distance.Length() < 190.0f) {
        return enAIState_Idle;
    }
    // 納品が完了した
    if (npc->m_target->GetStateMachine()->GetTargetFood() == nullptr) {
        return enAIState_FreeMove;
    }
    return enAIState_Invalid;
}