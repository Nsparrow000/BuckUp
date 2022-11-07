//=============================================================================
// �G�t�F�N�g�������[�h������ [Load.h]
// Author : �����G��
//=============================================================================
#ifndef _LOADEFFECT_H_
#define _LOADEFFECT_H_

#include "main.h"
#include <vector>
#include <map>

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PRESET (6)
#define PRESETCALL_TEXT ("data/PresetCall.txt")

class CLoadEffect
{
public:
	CLoadEffect();
	~CLoadEffect();

	static void EffectStateLoad(const char *aFileName);	//�G�t�F�N�g�̃X�e�[�^�X

	static int GetPresetTotal2D() { return m_Total2d; }
	static int GetPresetTotal3D() { return m_Total3d; }

	//------------------------------------------
	// �v���Z�b�g�Ăяo���\����
	//------------------------------------------
	typedef struct
	{
		std::vector<int> m_nDelay;					// �Ăяo���Ă��牽�t���[����ɐ������邩
		std::vector<int> m_nPresetNum;				// �����G�t�F�N�g���Ăяo����
		std::vector<std::vector<int>> m_nType;		// �G�t�F�N�g�̃^�C�v
		int m_CallMax;								// ���̃v���Z�b�g�Ɏg���R�[����
	}CALL_PRESET;

	static void PresetCallLoad(const char *aFileName);	// �v���Z�b�g���Ăяo���e�L�X�g��ǂݍ��ފ֐�

	// �v���Z�b�g�Ăяo�����̎擾
	static CALL_PRESET GetCallPreset(int nID) { return m_CallPreset[nID]; }
	static int GetPresetName(std::string sName) { return m_Name[sName]; }


private:
	static int m_Total2d;
	static int m_Total3d;

	static CALL_PRESET m_CallPreset[MAX_PRESET];			// �v���Z�b�g�̌Ăяo���\����
	static std::map<std::string, int> m_Name;				// �v���Z�b�g�̖��O
	static int m_CallMax;				// �v���Z�b�g����

};

#endif // !_LOADEFFECT_H_