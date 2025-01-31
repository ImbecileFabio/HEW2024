//==================================================
// [AudioManager.h] �I�[�f�B�I�}�l�[�W���[
// ���ҁF���J����
//--------------------------------------------------
// �����F�T�E���h�̊Ǘ�
// 
// �@�\�FGetInstance()			�C���X�^���X�̎擾	
// 		
//		Play(�T�E���h���x��)	�T�E���h�̍Đ�
//		Stop(�T�E���h���x��)	�T�E���h�̒�~
//		Resume(�T�E���h���x��)	�T�E���h�̍ĊJ
// 
// 		SetVolume(�T�E���h���x��, 0.0f�`1.0f�̐��l)			�{�����[���̐ݒ�
//		SetCategoryVolume(�T�E���h�J�e�S��, 0.0f�`1.0f�̐��l)	�J�e�S�����̃{�����[���̐ݒ�
// 
// 		GetPlayingState(�T�E���h���x��)	�T�E���h�̍Đ���Ԃ̎擾
//==================================================

#pragma once
#include <xaudio2.h>
#include <iostream>
#include <memory>
#include <list>
#include "GameObjects/GameObject.h"

// �T�E���h�t�@�C��
typedef enum {
	// BGM
	SoundLabel_TitleBGM = 0,			// �^�C�g��BGM
	SoundLabel_StageBGM,				// �X�e�[�WBGM
	SoundLabel_ResultBGM,				// ���U���gBGM
	// �U��q�֘ASE
	SoundLabel_PendulumHitSE,			// �@��SE
	SoundLabel_PendulumCreakSE,			// �a��SE
	// ���{�b�g�֘ASE
	SoundLabel_RobotMoveSE,				// ���sSE
	SoundLabel_RobotLandingSE,			// ���nSE
	// �X�e�[�W�A���U���g�֘ASE
	SoundLabel_StageGearSE,				// �A�C�e���擾SE
	SoundLabel_StageResultGearSE,		// ���U���g�ŃA�C�e�����Ƃ܂鎞��SE
	SoundLabel_StageRewindSteamSE,		// �����߂���SE
	// UI�֘ASE
	SoundLabel_UIDecisionSE,			// UI�̌���Ƃ���SE
	SoundLabel_UICancelSE,				// UI�̌���Ƃ���SE
	SoundLabel_UISceneChangeSE,			// ���Ԃ����SE
	SoundLabel_UICursorMoveSE,			// �J�[�\���ړ�SE
	// �M�~�b�N�֘ASE
	SoundLabel_GimmickLiftMoveSE0,		// ���t�g�ړ�SE
	SoundLabel_GimmickLiftMoveSE1,		// ���t�g�ړ�SE
	SoundLabel_GimmickLiftMoveSE2,		// ���t�g�ړ�SE
	SoundLabel_GimmickLiftMoveSE3,		// ���t�g�ړ�SE
	SoundLabel_GimmickLiftMoveSE4,		// ���t�g�ړ�SE
	SoundLabel_GimmickWeakFloorStaySE0,	// �ア���̑ҋ@SE
	SoundLabel_GimmickWeakFloorStaySE1,	// �ア���̑ҋ@SE
	SoundLabel_GimmickWeakFloorStaySE2,	// �ア���̑ҋ@SE
	SoundLabel_GimmickWeakFloorStaySE3,	// �ア���̑ҋ@SE
	SoundLabel_GimmickWeakFloorStaySE4,	// �ア���̑ҋ@SE
	SoundLabel_GimmickWeakFloorDropSE,	// �ア���̗���SE
	SoundLabel_GimmickSmokeSE0,			// ��SE
	SoundLabel_GimmickSmokeSE1,			// ��SE
	SoundLabel_GimmickSmokeSE2,			// ��SE
	SoundLabel_GimmickSmokeSE3,			// ��SE
	SoundLabel_GimmickSmokeSE4,			// ��SE

	SoundLabel_MAX,
} SOUND_LABEL;
typedef enum {
	BGM = 0,
	SE,

	SoundCategory_MAX
}SOUND_CATEGORY;

class AudioManager {
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR filename;				// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;						// true�Ń��[�v�B�ʏ�ABGM��ture�ASE��false�B
		SOUND_CATEGORY soundCategory;	// BGM��SE�ǂ���̃T�u�~�b�N�X�{�C�X��K�p���邩�̎��ʎq
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		// BGM
		{ "Asset/Sound/BGM/TitleBGM.wav",				true,  BGM },	// 0.�^�C�g��BGM
		{ "Asset/Sound/BGM/StageBGM1.1.wav",			true,  BGM },	// 1.�X�e�[�WBGM
		{ "Asset/Sound/BGM/ResultBGM.wav",				true,  BGM },	// 2.���U���gBGM
		// �U��q�֘ASE
		{ "Asset/Sound/SE/PendulumHit.wav",				false, SE },	// 3.�@��SE
		{ "Asset/Sound/SE/PendulumCreak.wav",			false, SE },	// 4.�a��SE
		// ���{�b�g�֘ASE
		{ "Asset/Sound/SE/RobotMove.wav",				false, SE },	// 5.���sSE
		{ "Asset/Sound/SE/RobotLanding1.1.wav",			false, SE },	// 6.���nSE
		// �X�e�[�W�A���U���g�֘ASE
		{ "Asset/Sound/SE/StageGear1.1.wav",			false, SE },	// 7.�A�C�e���擾SE
		{ "Asset/Sound/SE/StageResultGear.wav",			false, SE },	// 8.���U���g�ŃA�C�e�����Ƃ܂鎞��SE
		{ "Asset/Sound/SE/StageRewindSmoke.wav",		false, SE },	// 9.�����߂���SE
		// UI�֘ASE
		{ "Asset/Sound/SE/UIDecision.wav",				false, SE },	// 10.UI�̌���Ƃ���SE
		{ "Asset/Sound/SE/UICancel.wav",				false, SE },	// 11.UI�̌���Ƃ���SE
		{ "Asset/Sound/SE/UISceneChange.wav",			false, SE },	// 12.���Ԃ����SE
		{ "Asset/Sound/SE/UICursorMove.wav",			false, SE },	// 13.�J�[�\���ړ�SE
		// �M�~�b�N�֘ASE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.���t�g�ړ�SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.���t�g�ړ�SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.���t�g�ړ�SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.���t�g�ړ�SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.���t�g�ړ�SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.�ア���̑ҋ@SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.�ア���̑ҋ@SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.�ア���̑ҋ@SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.�ア���̑ҋ@SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.�ア���̑ҋ@SE
		{ "Asset/Sound/SE/GimmickWeakFloorDrop1.1.wav",	false, SE },	// 16.�ア���̗���SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.��SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.��SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.��SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.��SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.��SE

	};

	IXAudio2* m_pXAudio2 = nullptr;
	IXAudio2MasteringVoice* m_pMasteringVoice = nullptr;
	IXAudio2SubmixVoice* m_pSubmixVoice[SoundCategory_MAX] = { nullptr };
	IXAudio2SourceVoice* m_pSourceVoice[SoundLabel_MAX] = { nullptr };
	WAVEFORMATEXTENSIBLE m_wfx[SoundLabel_MAX] = {}; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SoundLabel_MAX] = {};
	BYTE* m_DataBuffer[SoundLabel_MAX] = { nullptr };
	XAUDIO2_SEND_DESCRIPTOR m_sendDescriptor[SoundCategory_MAX] = {};
	XAUDIO2_VOICE_SENDS m_sendList[SoundCategory_MAX] = {};

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	static std::unique_ptr<AudioManager> m_instance;
public:
	AudioManager();
	~AudioManager();

	static std::unique_ptr<AudioManager>& GetInstance() {
		if (!m_instance) m_instance = std::make_unique<AudioManager>();
		return m_instance;
	}

	HRESULT General_Init(void);
	void Sound_Init(void);
	void Uninit(void);

	void Play(SOUND_LABEL _label);
	void Play(GameObject::TypeID _id, int _fier);
	void Stop(SOUND_LABEL _label);
	void Stop(GameObject::TypeID _id, int _fier);
	void Resume(SOUND_LABEL _label);
	void Pause(SOUND_LABEL _label);

	void SetVolume(SOUND_LABEL _label, float _volume);
	void SetCategoryVolume(SOUND_CATEGORY _category, float _volume);

	bool GetPlayingState(SOUND_LABEL _label);
	bool GetPlayingState(GameObject::TypeID _id, int _fier);
};