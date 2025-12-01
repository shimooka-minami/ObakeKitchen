#include "stdafx.h"
#include "NPCController.h"

#include "actor/Player.h"
#include "actor/StateMachine.h"

/** 名前被り等の衝突を防ぐため */
namespace
{
    // @todo for test
    constexpr float PLAYER_MOVE_SPEED = 3.0f; // 移動速度
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
        return enAIState_FreeMove;
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