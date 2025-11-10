#include "stdafx.h"
#include "system/system.h"

#include<InitGUID.h>
#include<dxgidebug.h>

//#include "Game.h"

#include "core/ParameterManager.h"
#include "core/Fade.h"
#include "effect/EffectManager.h"
#include "sound/SoundManager.h"
#include "scene/SceneManager.h"


void ReportLiveObjects()
{
	IDXGIDebug* pDxgiDebug;

	typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
	HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
	fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

	DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);

	// 出力。
	pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_DETAIL);
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	// @todo for test
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	// フェード生成
	auto* fadeObject = NewGO<FadeObject>(100, "fadeObject");
	// パラメーターマネージャー生成
	ParameterManager::CreateInstance();
	// サウンドマネージャー生成
	SoundManager::CreateInstance();
	// エフェクトマネージャーオブジェクト生成
	auto* effectManagerObject = NewGO<EffectManagerObject>(0, "effectManagerObject");
	// シーン管理用のゲームオブジェクト生成
	auto* sceneManagerObject = NewGO<SceneManagerObject>(0, "sceneManagerObject");

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		if (g_pad[0]->IsTrigger(enButtonA) ){
			g_pad[0]->SetVibration(/*durationSec=*/0.5f, /*normalizedPower=*/1.0f);
		}
		// サウンドの更新
		SoundManager::Get().Update();
		K2Engine::GetInstance()->Execute();
	}

	// シーン管理破棄
	DeleteGO(sceneManagerObject);
	// エフェクトマネージャーオブジェクト破棄
	DeleteGO(effectManagerObject);
	// サウンドマネージャー破棄
	SoundManager::DestroyInstance();
	// パラメーターマネージャー破棄
	ParameterManager::DestroyInstance();
	// フェード破棄
	DeleteGO(fadeObject);

	K2Engine::DeleteInstance();

#ifdef _DEBUG
	ReportLiveObjects();
#endif // _DEBUG
	return 0;
}

