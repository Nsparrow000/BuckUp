//=============================================================================
// �x���t���G�t�F�N�g�v���Z�b�g�Ăяo���N���X
// Author : ������
//=============================================================================
#ifndef _PRESETDELAYSET_H_
#define _PRESETDELAYSET_H_
#include "scene3d.h"
#include "loadeffect.h"
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CPresetDelaySet : public CScene3D
{
public:
	CPresetDelaySet(int nPriority);	// �R���X�g���N�^
	~CPresetDelaySet();						// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot);	 // ������
	void Uninit();					 // �I��
	void Update();					 // �X�V
	void Draw();					 // �`��

	static CPresetDelaySet *Create(int nArray, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot);
	static CPresetDelaySet *Create(std::string sName, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot);

private:
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_Endpos;	//��r�p(�^�[�Q�b�g)
	D3DXVECTOR3 m_rot;	//��]

	int m_nDelay;
	int m_nCallCnt;
	int m_nArray;
	bool m_bUninit;
};									 

#endif