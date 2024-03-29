//=============================================================================
// 2D側エフェクト管理[2DScene.h]
// Author : 佐藤秀亮
//=============================================================================
//*****************************************************************************
//インクルード
//*****************************************************************************
#if 1
#include "2DScene.h"
#include "Fade.h"

#include "keyboard.h"

#include "seteffect.h"
#include "load.h"
#include "control.h"

#include "Butten.h"

#include "LoadEffect.h"
#include "PresetSetEffect.h"

#endif

//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
#define SET_TEXT_2D "data/2DSetTex.txt"
#define LOAD_PRESET_TEXT "data/Preset.txt"

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
C2DScene::C2DScene()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
C2DScene::~C2DScene()
{
}
#endif

//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT C2DScene::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	//m_pGamePad = CManager::GetGamepad();

	m_Set = CSetEffect::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),10, 10, -1);


	CLoad::LoadButten(SET_TEXT_2D);
	CControl::SetPlayerMode(false);

	//フェード
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	return S_OK;
}

//*****************************************************************************
// 終了
//***************************************************************************** 
void C2DScene::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void C2DScene::Update()
{
	m_pSetpos = m_Set->GetPos();

	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		{

			CFade::SetFade(CManager::MODE_3D);
			CButten::ReSetButten();

			CButten::ResetPatten();
			CControl::SetPattern(0);
		}

		if (m_pKeyboard->GetKey(DIK_F2) == true)
		{
			for (int nCnt = 0; nCnt < CLoadEffect::GetPresetTotal2D(); nCnt++)
			{

				CPresetEffect::SetEffect2D(nCnt, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), {}, {});
			}
		}

	}

}

#if 1
//*****************************************************************************
//描画
//***************************************************************************** 
void C2DScene::Draw()
{

}

//*****************************************************************************
//描画
//***************************************************************************** 
C2DScene *C2DScene::Create()
{
	C2DScene *p2DScene = NULL;
	p2DScene = new C2DScene;		//メモリ確保
								//NULLチェック
	if (p2DScene != NULL)
	{
		p2DScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return p2DScene;
}
#endif

#if 1
#endif
