//=============================================================================
// 3D�����G�t�F�N�g���� [Fountain.cpp]
// Author : �����G��
//=============================================================================
#include "Fountain.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFountain::CFountain(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFountain::~CFountain()
{

}

//=============================================================================
// ������
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
// �I��
//=============================================================================
void CFountain::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CFountain::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void CFountain::Draw()
{
	CBillEffect::Draw();
}

//=============================================================================
// �쐬
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