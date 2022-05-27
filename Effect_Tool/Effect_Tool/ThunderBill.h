//=============================================================================
// (雷（仮称）)エフェクト処理 [ThunderBill.h]
// Author : 佐藤秀亮
//=============================================================================
#include "main.h"
#include "billEffect.h"

class CCamera;

class CThunderBill : public CBillEffect
{
public:
	CThunderBill(int nPriority);
	~CThunderBill();

	HRESULT Init(D3DXVECTOR3 pos,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex,
		int nLife,
		float Destance,
		D3DXVECTOR2 TexMove,
		D3DXVECTOR2 TexNum,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		float fHigth);

	void Uninit();
	void Update();
	void Draw();

	static CThunderBill *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex,
		int nLife,
		float Destance,
		D3DXVECTOR2 TexMove,
		D3DXVECTOR2 TexNum,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		float fHigth);
private:
	CCamera *m_pCamera;

	D3DXVECTOR3 m_pos;	//出現位置
	D3DXVECTOR3 m_pos2;	//出現位置上
	float m_Rot;	//出現位置上

	float m_fHigth;

};