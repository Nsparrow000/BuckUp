//*****************************************************************************
// 回転エフェクトの親処理(Rotate3d.h)
// Author : 佐藤秀亮
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
	} EFFECT_TIME;	//エフェクトの状態

	typedef enum
	{
		TYPE_PARTICLE,
		TYPE_TRAJECT,
		TYPE_MAX,
	} EFFECT_TYPE;	//何のエフェクト出すか

	typedef enum
	{
		TYPE_NOMAL,
		TYPE_MOVERAND,
		MOVETYPE_MAX,
	} MOVE_TYPE;

	typedef enum
	{
		TYPE_EIGHT,	//八の字
		TYPE_VERTICAL,	//縦回転
		TYPE_BESIDE,	//横回転
		TYPE_DIAGONAL_RIGHT,	//斜め右
		TYPE_DIAGONAL_LEFT,	//斜め左
		TYPE_BESIDE_NO_RAND,	//高さランド無し横回転
		TYPE_RING,	//輪
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
	TYPE_MOVING m_MoveingType;	//動きタイプ

	bool m_bUninit;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Oldpos;

	D3DXVECTOR3 m_Size;
	D3DXVECTOR3 m_AddSize;
	D3DCOLORVALUE m_Color;
	D3DCOLORVALUE m_MinColor;

	float m_nDistanse;	//現在の離れてる値
	float m_nDefaultDistanse;	//デフォルト

	float m_nAddDistance;
	float m_fAngle;
	float m_fAddAngle;
	float m_fRandAngle;
	float m_fRandAngle2;
	int m_nBuckTime;	//距離が縮まるまでの時間
	float m_fActive;	//アクティブになるまでの距離

	bool m_bSpecify;	//角度と発生点指定
	int m_nTex;
	int m_nSynthetic;
	int m_nLife;
	int m_ParticleLife;
	int m_PatternAnim;

	int m_MovePattern;	//動きパターン
};

#endif