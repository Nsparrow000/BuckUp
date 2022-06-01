//=============================================================================
// �x�W�F�Ȑ��ړ��r���{�[�h���� [BezierBill.cpp]
// Author : �����G��
//=============================================================================
#include "BezierBillh.h"
#include "manager.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBezierBill::CBezierBill(int nPriority) : CBillEffect(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBezierBill::~CBezierBill()
{

}

//*****************************************************************************
//������
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

	//�x�W�F�v�Z
	//����_
	double P01[3], P12[3], P02[3];

		m_Bezier.x = 0;
		m_Bezier.y = 0;
		m_Bezier.u = 0;

		//�ʉߓ_�J�E���^�[
		m_Bezier.Counter = 0;
		m_Bezier.Counter2 = 0;

		//�ʉߓ_
		m_Bezier.DivNum = m_Speed;

		//�����_
		m_Bezier.P0[0] = pos.x;
		m_Bezier.P0[1] = pos.y;
		m_Bezier.P0[2] = pos.z;

		//����_
		m_Bezier.P1[0] = pos.x - randCont * sinf(m_fRandAngle) * cosf(m_fRandAngle2);
		m_Bezier.P1[1] = pos.y - m_ControlBezier.y * cosf(m_fRandAngle);
		m_Bezier.P1[2] = pos.z - randCont * sinf(m_fRandAngle) * sinf(m_fRandAngle2);

		//�ڕW�n�_
		m_Bezier.P2[0] = m_Target.x;
		m_Bezier.P2[1] = m_Target.y;
		m_Bezier.P2[2] = m_Target.z;

		m_Bezier.f = true;

	if (m_Bezier.f == true)
	{
		m_Bezier.u = (1.0 / m_Bezier.DivNum) * m_Bezier.Counter;

		//�v�Z��
		P01[0] = (1.0 - m_Bezier.u) * m_Bezier.P0[0] + m_Bezier.u * m_Bezier.P1[0];
		P01[1] = (1.0 - m_Bezier.u) * m_Bezier.P0[1] + m_Bezier.u * m_Bezier.P1[1];
		P01[2] = (1.0 - m_Bezier.u) * m_Bezier.P0[2] + m_Bezier.u * m_Bezier.P1[2];

		P12[0] = (1.0 - m_Bezier.u) * m_Bezier.P1[0] + m_Bezier.u * m_Bezier.P2[0];
		P12[1] = (1.0 - m_Bezier.u) * m_Bezier.P1[1] + m_Bezier.u * m_Bezier.P2[1];
		P12[2] = (1.0 - m_Bezier.u) * m_Bezier.P1[2] + m_Bezier.u * m_Bezier.P2[2];

		//�ʒu
		P02[0] = (1.0 - m_Bezier.u) * P01[0] + m_Bezier.u * P12[0];
		P02[1] = (1.0 - m_Bezier.u) * P01[1] + m_Bezier.u * P12[1];
		P02[2] = (1.0 - m_Bezier.u) * P01[2] + m_Bezier.u * P12[2];

		m_Bezier.x = (int)P02[0];
		m_Bezier.y = (int)P02[1];
		m_Bezier.z = (int)P02[2];

		m_pos = D3DXVECTOR3(m_Bezier.x, m_Bezier.y, m_Bezier.z);

		m_Bezier.Counter++;

		// �����J�E���^�[���������ɒB���Ă�����O�ɖ߂�
		if (m_Bezier.Counter == m_Bezier.DivNum)
		{
			m_Bezier.Counter = 0;
			m_Bezier.f = false;//�폜
			m_bUninit = true;
		}
	}


	SetPos(m_pos);
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CBezierBill::Uninit()
{
	CBillEffect::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CBezierBill::Update()
{
	double P01[3], P12[3], P02[3];

	if (m_Bezier.f == true)
	{
		m_Bezier.u = (1.0 / m_Bezier.DivNum) * m_Bezier.Counter;

		P01[0] = (1.0 - m_Bezier.u) * m_Bezier.P0[0] + m_Bezier.u * m_Bezier.P1[0];
		P01[1] = (1.0 - m_Bezier.u) * m_Bezier.P0[1] + m_Bezier.u * m_Bezier.P1[1];
		P01[2] = (1.0 - m_Bezier.u) * m_Bezier.P0[2] + m_Bezier.u * m_Bezier.P1[2];

		P12[0] = (1.0 - m_Bezier.u) * m_Bezier.P1[0] + m_Bezier.u * m_Bezier.P2[0];
		P12[1] = (1.0 - m_Bezier.u) * m_Bezier.P1[1] + m_Bezier.u * m_Bezier.P2[1];
		P12[2] = (1.0 - m_Bezier.u) * m_Bezier.P1[2] + m_Bezier.u * m_Bezier.P2[2];


		P02[0] = (1.0 - m_Bezier.u) * P01[0] + m_Bezier.u * P12[0];
		P02[1] = (1.0 - m_Bezier.u) * P01[1] + m_Bezier.u * P12[1];
		P02[2] = (1.0 - m_Bezier.u) * P01[2] + m_Bezier.u * P12[2];


		m_Bezier.x = (int)P02[0];
		m_Bezier.y = (int)P02[1];
		m_Bezier.z = (int)P02[2];

		m_pos = D3DXVECTOR3(m_Bezier.x, m_Bezier.y, m_Bezier.z);

		m_Bezier.Counter++;

		// �����J�E���^�[���������ɒB���Ă�����O�ɖ߂�
		if (m_Bezier.Counter == m_Bezier.DivNum)
		{
			m_Bezier.Counter = 0;
			m_Bezier.f = false;//�폜
			m_bUninit = true;
		}
	}


	SetPos(m_pos);

	CBillEffect::Update();
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CBezierBill::Draw()
{
	CBillEffect::Draw();
}

//*****************************************************************************
//�쐬
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