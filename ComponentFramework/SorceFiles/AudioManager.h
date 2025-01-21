//==================================================
// [AudioManager.h] �I�[�f�B�I�}�l�[�W���[
// ���ҁF���J����
//--------------------------------------------------
// �����F�T�E���h�̊Ǘ�
// 
// �@�\�F	Init()	������
//		Uninit()	���		
// 		
//		Play(�T�E���h���x��)	�T�E���h�̍Đ�
//		Stop(�T�E���h���x��)	�T�E���h�̒�~
//		Resume(�T�E���h���x��)	�T�E���h�̍ĊJ
// 
// 		SetVolume(�T�E���h���x��, 0.0f�`1.0f�̐��l)			�{�����[���̐ݒ�
//		SetCategoryVolume(�T�E���h�J�e�S��, 0.0f�`1.0f�̐��l)	�J�e�S�����̃{�����[���̐ݒ�
//==================================================

#pragma once
#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum {
	SoundLabel_TitleBGM = 0,		// �^�C�g��BGM
	SoundLabel_StageBGM,			// �X�e�[�WBGM
	SoundLabel_HitSE,				// �@��SE
	SoundLabel_LandingSE,			// ���nSE
	SoundLabel_ItemGet,				// �A�C�e���擾SE

	SoundLabel_MAX,
} SOUND_LABEL;
typedef enum {
	BGM = 0,
	SE,

	SoundTag_MAX
}SOUND_CATEGORY;

class AudioManager {
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
		SOUND_CATEGORY soundCategory;	// BGM��SE�ǂ���̃T�u�~�b�N�X�{�C�X��K�p���邩�̎��ʎq
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		{ "Asset/Sound/BGM/Title_BGM.wav",	true,  BGM },	// �^�C�g��BGM
		{ "Asset/Sound/BGM/StageBGM.wav",	true,  BGM },	// �X�e�[�WBGM
		{ "Asset/Sound/SE/�@����.wav",		false, SE },	// �@��SE
		{ "Asset/Sound/SE/���n1.wav",		false, SE },	// ���nSE
		{ "Asset/Sound/SE/�M�A�l��.wav",	false, SE }		// �A�C�e���擾SE
	};

	IXAudio2* m_pXAudio2 = nullptr;
	IXAudio2MasteringVoice* m_pMasteringVoice = nullptr;
	IXAudio2SubmixVoice* m_pSubmixVoice[SoundTag_MAX];
	IXAudio2SourceVoice* m_pSourceVoice[SoundLabel_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SoundLabel_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SoundLabel_MAX];
	BYTE* m_DataBuffer[SoundLabel_MAX];
	XAUDIO2_SEND_DESCRIPTOR m_sendDescriptor[SoundTag_MAX];
	XAUDIO2_VOICE_SENDS m_sendList[SoundTag_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	HRESULT Init(void);
	void Uninit(void);

	void Play(SOUND_LABEL _label);
	void Stop(SOUND_LABEL _label);
	void Resume(SOUND_LABEL _label);

	void SetVolume(SOUND_LABEL _label, float _volume);
	void SetCategoryVolume(SOUND_CATEGORY _category, float _volume);
	void SetSpeed(SOUND_LABEL _label, float _spped);
};
