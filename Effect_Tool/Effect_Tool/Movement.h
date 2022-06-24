//*****************************************************************************
// (移動する)エフェクト処理 [Movement.h]
// Author : 佐藤秀亮
//*****************************************************************************
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "Effect.h"

class CMovement : public CEffect
{
public:
	CMovement(int nPriority);
	~CMovement();

	HRESULT Init(D3DXVECTOR3 pos,
		D3DXVECTOR2 move,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		D3DXVECTOR2 Size,
		D3DXVECTOR2 MinSize,
		int nLife,
		int nType,
		D3DXVECTOR2 AddMovement,
		int nSynthetic,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		ANIMPATTERN AnimPattern);

	void Uninit();
	void Update();
	void Draw();

	static CMovement*Create(D3DXVECTOR3 pos,
		D3DXVECTOR2 move,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		D3DXVECTOR2 Size,
		D3DXVECTOR2 MinSize,
		int nLife,
		int nType,
		D3DXVECTOR2 AddMovement,
		int nSynthetic,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		ANIMPATTERN AnimPattern);
private:
	D3DXVECTOR2 m_move;			//移動
	D3DXVECTOR2 m_Addpos;		//慣性
};

#endif // !_MOVEMENT_H_
