//=============================================================================
// 3D噴水エフェクト処理 [Fountain.cpp]
// Author : 佐藤秀亮
//=============================================================================
#include "Fountain.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CFountain::CFountain(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CFountain::~CFountain()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CFountain::Init(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nTex, int nLife,
	D3DXVECTOR2 TexNum,
	D3DXVECTOR2 TexMove,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	ANIMPATTERN AnimPattern,
	D3DXVECTOR3 move,
	D3DXVECTOR3 Target)
{
	CBillEffect::Init(Size, MinSize, color, Mincolor, nTex, nLife, TexNum, TexMove, nAnimCounter, nSplit, AnimPattern);

	D3DXVECTOR3 Target = Target;
	D3DXVECTOR3 V = pos - Target;

	m_fAngle = atan2(V.x, V.z);

	m_pos = pos;
	m_move = move;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CFountain::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CFountain::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void CFountain::Draw()
{
	CBillEffect::Draw();
}

//=============================================================================
// 作成
//=============================================================================
CFountain *CFountain::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nTex, int nLife,
	D3DXVECTOR2 TexNum,
	D3DXVECTOR2 TexMove,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	ANIMPATTERN AnimPattern,
	D3DXVECTOR3 move,
	D3DXVECTOR3 Target)
{
	CFountain *pFountain = new CFountain(CManager::PRIORITY_EFFECT);

	if (pFountain != NULL)
	{
		pFountain->Init(pos, Size, MinSize, color, Mincolor, nTex, nLife, TexNum, TexMove, nAnimCounter, nSplit, AnimPattern, move, Target);
	}

	return pFountain;
}