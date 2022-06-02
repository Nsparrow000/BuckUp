//=============================================================================
// ベジェ曲線移動ビルボード処理 [BezierBill.cpp]
// Author : 佐藤秀亮
//=============================================================================
#include "BezierBillh.h"
#include "manager.h"

#include "Trajectory.h"
#include "control.h"
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBezierBill::CBezierBill(int nPriority) : CBillEffect(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBezierBill::~CBezierBill()
{

}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CBezierBill::Init(D3DXVECTOR3 Size,
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
	D3DXVECTOR3 ControlBezier)
{
	CBillEffect::Init(Size, MinSize, color, Mincolor, nTex, nLife, TexNum, TexMove, nAnimCounter, nSplit);

	m_Size = Size;
	m_Target = Target;
	m_ControlBezier = ControlBezier;
	m_Speed = Speed;
	m_fRandAngle = CIRCLE2;
	m_fRandAngle2 = CIRCLE2;
	m_nDistanse = 200;
	float randCont = float(rand() % (int)m_ControlBezier.x) - float(rand() % (int)m_ControlBezier.x);

	//ベジェ計算
	//制御点
	double P01[3], P12[3], P02[3];

		m_Bezier.x = 0;
		m_Bezier.y = 0;
		m_Bezier.u = 0;

		//通過点カウンター
		m_Bezier.Counter = 0;
		m_Bezier.Counter2 = 0;

		//通過点
		m_Bezier.DivNum = m_Speed;

		//発生点
		m_Bezier.P0[0] = m_Target.x;
		m_Bezier.P0[1] = m_Target.y;
		m_Bezier.P0[2] = m_Target.z;

		//制御点
		m_Bezier.P1[0] = pos.x + m_ControlBezier.z + randCont * sinf(m_fRandAngle) * cosf(m_fRandAngle2);
		m_Bezier.P1[1] = pos.y + m_ControlBezier.y/* * cosf(m_fRandAngle)*/;
		m_Bezier.P1[2] = pos.z + m_ControlBezier.z + randCont * sinf(m_fRandAngle) * sinf(m_fRandAngle2);

		//目標地点
		m_Bezier.P2[0] = pos.x;
		m_Bezier.P2[1] = pos.y;
		m_Bezier.P2[2] = pos.z;

		m_Bezier.f = true;

	if (m_Bezier.f == true)
	{
		m_Bezier.u = (1.0 / m_Bezier.DivNum) * m_Bezier.Counter;

		//計算式
		P01[0] = (1.0 - m_Bezier.u) * m_Bezier.P0[0] + m_Bezier.u * m_Bezier.P1[0];
		P01[1] = (1.0 - m_Bezier.u) * m_Bezier.P0[1] + m_Bezier.u * m_Bezier.P1[1];
		P01[2] = (1.0 - m_Bezier.u) * m_Bezier.P0[2] + m_Bezier.u * m_Bezier.P1[2];

		P12[0] = (1.0 - m_Bezier.u) * m_Bezier.P1[0] + m_Bezier.u * m_Bezier.P2[0];
		P12[1] = (1.0 - m_Bezier.u) * m_Bezier.P1[1] + m_Bezier.u * m_Bezier.P2[1];
		P12[2] = (1.0 - m_Bezier.u) * m_Bezier.P1[2] + m_Bezier.u * m_Bezier.P2[2];

		//位置
		P02[0] = (1.0 - m_Bezier.u) * P01[0] + m_Bezier.u * P12[0];
		P02[1] = (1.0 - m_Bezier.u) * P01[1] + m_Bezier.u * P12[1];
		P02[2] = (1.0 - m_Bezier.u) * P01[2] + m_Bezier.u * P12[2];

		m_Bezier.x = (int)P02[0];
		m_Bezier.y = (int)P02[1];
		m_Bezier.z = (int)P02[2];

		m_pos = D3DXVECTOR3(m_Bezier.x, m_Bezier.y, m_Bezier.z);

		m_Bezier.Counter++;

		// もしカウンターが分割数に達していたら０に戻す
		if (m_Bezier.Counter == m_Bezier.DivNum)
		{
			m_Bezier.Counter = 0;
			m_Bezier.f = false;//削除
			m_bUninit = true;
		}
	}

	m_Oldpos = m_pos;
	SetPos(m_pos);
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CBezierBill::Uninit()
{
	CBillEffect::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CBezierBill::Update()
{
	D3DXVECTOR3 pos;

	//プレイヤー追従がON
	CScene *pScene = GetScene(CManager::PRIORITY_SET);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_PLAYER)
		{
			pos = pScene->GetPos();
		}
		pScene = pSceneNext;
	}
	double P01[3], P12[3], P02[3];

	if (m_Bezier.f == true)
	{
		m_Bezier.u = (1.0 / m_Bezier.DivNum) * m_Bezier.Counter;

		P01[0] = (1.0 - m_Bezier.u) * m_Bezier.P0[0] + m_Bezier.u * m_Bezier.P1[0];
		P01[1] = (1.0 - m_Bezier.u) * m_Bezier.P0[1] + m_Bezier.u * m_Bezier.P1[1];
		P01[2] = (1.0 - m_Bezier.u) * m_Bezier.P0[2] + m_Bezier.u * m_Bezier.P1[2];

		P12[0] = (1.0 - m_Bezier.u) * m_Bezier.P1[0] + m_Bezier.u * pos.x;
		P12[1] = (1.0 - m_Bezier.u) * m_Bezier.P1[1] + m_Bezier.u * pos.y;
		P12[2] = (1.0 - m_Bezier.u) * m_Bezier.P1[2] + m_Bezier.u * pos.z;


		P02[0] = (1.0 - m_Bezier.u) * P01[0] + m_Bezier.u * P12[0];
		P02[1] = (1.0 - m_Bezier.u) * P01[1] + m_Bezier.u * P12[1];
		P02[2] = (1.0 - m_Bezier.u) * P01[2] + m_Bezier.u * P12[2];


		m_Bezier.x = (int)P02[0];
		m_Bezier.y = (int)P02[1];
		m_Bezier.z = (int)P02[2];

		m_pos = D3DXVECTOR3(m_Bezier.x, m_Bezier.y, m_Bezier.z);

		m_Bezier.Counter++;

		// もしカウンターが分割数に達していたら０に戻す
		if (m_Bezier.Counter == m_Bezier.DivNum)
		{
			m_Bezier.Counter = 0;
			m_Bezier.f = false;//削除
			m_bUninit = true;
		}
	}


	CTrajectory::Create(
		D3DXVECTOR3(m_pos.x, m_pos.y + CControl::GetSize(), m_pos.z),
		D3DXVECTOR3(m_pos.x, m_pos.y - CControl::GetSize(), m_pos.z),
		D3DXVECTOR3(m_Oldpos.x, m_Oldpos.y + CControl::GetSize(), m_Oldpos.z),
		D3DXVECTOR3(m_Oldpos.x, m_Oldpos.y - CControl::GetSize(), m_Oldpos.z),
		D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
		D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
		D3DXCOLOR((float)CControl::GetTrajectColor(1), (float)CControl::GetTrajectColor(2), (float)CControl::GetTrajectColor(3), (float)CControl::GetTrajectColor(4)),
		D3DXCOLOR((float)CControl::GetTrajectCol(1), (float)CControl::GetTrajectCol(2), (float)CControl::GetTrajectCol(3), (float)CControl::GetTrajectCol(4)),
		D3DXVECTOR3(0.0, CControl::GetSize(), 0.0),
		D3DXVECTOR3(0.0, CControl::GetChangeSize(), 0.0),
		CControl::GetTex(), 30);



	SetPos(m_pos);
	m_Oldpos = m_pos;
	CBillEffect::Update();
}

//*****************************************************************************
//描画
//*****************************************************************************
void CBezierBill::Draw()
{
	CBillEffect::Draw();
}

//*****************************************************************************
//作成
//*****************************************************************************
CBezierBill *CBezierBill::Create(D3DXVECTOR3 Size,
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
	D3DXVECTOR3 ControlBezier)
{
	CBezierBill * pBezierBill = NULL;
	pBezierBill = new CBezierBill(CManager::PRIORITY_EFFECT);
	if (pBezierBill != NULL)
	{
		pBezierBill->Init(Size, MinSize, color, Mincolor,
			nTex, nLife, TexNum, TexMove,
			nAnimCounter, nSplit,
			pos,
			Target,
			Speed,
			ControlBezier);
	}
	return pBezierBill;

}

//*****************************************************************************
//予測線
//*****************************************************************************
void CBezierBill::PredictTraject()
{
	double P01[3], P12[3], P02[3];
	m_Oldpos = m_pos;

	for (int i = 0; i < m_Bezier.DivNum; i++)
	{
		if (m_Bezier.f == true)
		{
			m_Bezier.u = (1.0 / m_Bezier.DivNum) * m_Bezier.Counter;

			//計算式
			P01[0] = (1.0 - m_Bezier.u) * m_Bezier.P0[0] + m_Bezier.u * m_Bezier.P1[0];
			P01[1] = (1.0 - m_Bezier.u) * m_Bezier.P0[1] + m_Bezier.u * m_Bezier.P1[1];
			P01[2] = (1.0 - m_Bezier.u) * m_Bezier.P0[2] + m_Bezier.u * m_Bezier.P1[2];

			P12[0] = (1.0 - m_Bezier.u) * m_Bezier.P1[0] + m_Bezier.u * m_Bezier.P2[0];
			P12[1] = (1.0 - m_Bezier.u) * m_Bezier.P1[1] + m_Bezier.u * m_Bezier.P2[1];
			P12[2] = (1.0 - m_Bezier.u) * m_Bezier.P1[2] + m_Bezier.u * m_Bezier.P2[2];

			//位置
			P02[0] = (1.0 - m_Bezier.u) * P01[0] + m_Bezier.u * P12[0];
			P02[1] = (1.0 - m_Bezier.u) * P01[1] + m_Bezier.u * P12[1];
			P02[2] = (1.0 - m_Bezier.u) * P01[2] + m_Bezier.u * P12[2];

			m_Bezier.x = (int)P02[0];
			m_Bezier.y = (int)P02[1];
			m_Bezier.z = (int)P02[2];


			m_Bezier.Counter++;
			m_pos = D3DXVECTOR3(m_Bezier.x, m_Bezier.y, m_Bezier.z);

			CTrajectory::Create(
				D3DXVECTOR3(m_Bezier.x, m_Bezier.y + 10, m_Bezier.z),
				D3DXVECTOR3(m_Bezier.x, m_Bezier.y - 10, m_Bezier.z),
				D3DXVECTOR3(m_Oldpos.x, m_Oldpos.y + 10, m_Oldpos.z),
				D3DXVECTOR3(m_Oldpos.x, m_Oldpos.y - 10, m_Oldpos.z),
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				D3DXCOLOR((float)CControl::GetTrajectColor(1), (float)CControl::GetTrajectColor(2), (float)CControl::GetTrajectColor(3), (float)CControl::GetTrajectColor(4)),
				D3DXCOLOR((float)CControl::GetTrajectCol(1), (float)CControl::GetTrajectCol(2), (float)CControl::GetTrajectCol(3), (float)CControl::GetTrajectCol(4)),
				D3DXVECTOR3(0.0, CControl::GetSize(), 0.0),
				D3DXVECTOR3(0.0, CControl::GetChangeSize(), 0.0),
				CControl::GetTex(), 10
			);
			m_Oldpos = D3DXVECTOR3(m_Bezier.x, m_Bezier.y, m_Bezier.z);
			// もしカウンターが分割数に達していたら０に戻す
			if (m_Bezier.Counter == m_Bezier.DivNum)
			{
				m_Bezier.Counter = 0;
				m_Bezier.f = false;//削除
			}
		}
	}


}
