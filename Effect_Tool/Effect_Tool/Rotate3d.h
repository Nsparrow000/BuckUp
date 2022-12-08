//*****************************************************************************
// ��]�G�t�F�N�g�̐e����(Rotate3d.h)
// Author : �����G��
//*****************************************************************************
#ifndef _ROTATE3D_H_
#define _ROTATE3D_H_

#include "plane.h"

class CRotate3D : public CPlane
{
public:
	typedef enum
	{
		START,
		ACTIVE,
		END,
		MAX,
	} EFFECT_TIME;	//�G�t�F�N�g�̏��

	typedef enum
	{
		TYPE_PARTICLE,
		TYPE_TRAJECT,
		TYPE_MAX,
	} EFFECT_TYPE;	//���̃G�t�F�N�g�o����

	typedef enum
	{
		TYPE_NOMAL,
		TYPE_MOVERAND,
		MOVETYPE_MAX,
	} MOVE_TYPE;

	typedef enum
	{
		TYPE_EIGHT,	//���̎�
		TYPE_VERTICAL,	//�c��]
		TYPE_BESIDE,	//����]
		TYPE_DIAGONAL_RIGHT,	//�΂߉E
		TYPE_DIAGONAL_LEFT,	//�΂ߍ�
		TYPE_BESIDE_NO_RAND,	//���������h��������]
		TYPE_RING,	//��
		MOVINGTYPE_MAX,
	} TYPE_MOVING;

	CRotate3D(int nPriority);
	~CRotate3D();

	HRESULT Init(D3DXVECTOR3 SetSize,
		D3DXVECTOR3 pos,
		D3DXVECTOR2 Tex,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 AddSize,
		D3DCOLORVALUE Color,
		D3DCOLORVALUE AddColor,
		float Distance,
		float AddDistance,
		float fAngle,
		float fAddAngle,
		int nTex,
		int Synthetic,
		int nLife,
		int nParticleLife,
		int nBuckTime,
		float fActive,
		int AnimPattern,
		EFFECT_TYPE EffectType,
		MOVE_TYPE MoveType,
		TYPE_MOVING MovingType,
		D3DXVECTOR3 rot);

	void Uninit();
	void Update();

	static CRotate3D *Create(D3DXVECTOR3 SetSize,
		D3DXVECTOR3 pos,
		D3DXVECTOR2 Tex,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 AddSize,
		D3DCOLORVALUE Color,
		D3DCOLORVALUE AddColor,
		float Distance,
		float AddDistance,
		float fAngle,
		float fAddAngle,
		int nTex,
		int Synthetic,
		int nLife,
		int nParticleLife,
		int nBuckTime,
		float fActive,
		int AnimPattern,
		EFFECT_TYPE EffectType,
		MOVE_TYPE MoveType,
		TYPE_MOVING MovingType,
		D3DXVECTOR3 rot);

private:
	EFFECT_TIME m_EffectTime;
	EFFECT_TYPE m_EffectType;
	MOVE_TYPE m_MoveType;
	TYPE_MOVING m_MoveingType;	//�����^�C�v

	bool m_bUninit;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Oldpos;

	D3DXVECTOR3 m_Size;
	D3DXVECTOR3 m_AddSize;
	D3DCOLORVALUE m_Color;
	D3DCOLORVALUE m_MinColor;

	float m_nDistanse;	//���݂̗���Ă�l
	float m_nDefaultDistanse;	//�f�t�H���g

	float m_nAddDistance;
	float m_fAngle;
	float m_fAddAngle;
	float m_fRandAngle;
	float m_fRandAngle2;
	int m_nBuckTime;	//�������k�܂�܂ł̎���
	float m_fActive;	//�A�N�e�B�u�ɂȂ�܂ł̋���

	bool m_bSpecify;	//�p�x�Ɣ����_�w��
	int m_nTex;
	int m_nSynthetic;
	int m_nLife;
	int m_ParticleLife;
	int m_PatternAnim;

	int m_MovePattern;	//�����p�^�[��
};

#endif