//=============================================================================
// ベジェ曲線移動ビルボード処理 [BezierBill.h]
// Author : 佐藤秀亮
//=============================================================================
#ifndef _BEZIERBILL_H_
#define _BEZIERBILL_H_

#include "plane.h"
#include "billEffect.h"

class CBezierBill : public CBillEffect
{
public:
	CBezierBill(int nPriority);	//コンストラクタ
	~CBezierBill();	//デストラクタ

	typedef struct
	{
		double x;//ホーミング座標
		double y;
		double z;

		double u;
		int Counter;
		int Counter2;
		int DivNum;
		double P0[3];
		double P1[3];
		double P2[3];

		bool f;
	} HOMING_BEZIER;

	HRESULT Init(D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex, int nLife,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 Target,
		int Speed,
		D3DXVECTOR3 ControlBezier);

	void Uninit();
	void Update();
	void Draw();

	static CBezierBill *Create(D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex, int nLife,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 Target,
		int Speed,
		D3DXVECTOR3 ControlBezier);

private:
	HOMING_BEZIER m_Bezier;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Size;

	D3DXVECTOR3 m_Target;	//目標地点
	D3DXVECTOR3 m_ControlBezier;	//制御点
	int m_Speed;	//スピード(ベジェの通過点数)

	float m_fRandAngle;
	float m_fRandAngle2;
	float m_nDistanse;

};

#endif // !_BEZIERBILL_H_
