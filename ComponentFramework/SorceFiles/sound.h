#pragma once
#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	SoundLabel_TitleBGM = 0,		// �^�C�g��BGM
	SoundLabel_StageBGM,			// �X�e�[�WBGM
	SoundLabel_HitSE,				// �@��SE
	SoundLabel_LandingSE,			// ���nSE
	SoundLabel_ItemGet,				// �A�C�e���擾SE

	SoundLabel_MAX,
} SOUND_LABEL;

class Sound {
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		//{"asset/BGM/������.wav", true },		// �T���v��BGM�i���[�v������̂�true�ݒ�j
		//{"asset/SE /������.wav", false},		// �T���v��SE�i���[�v���Ȃ��̂�false�ݒ�j

		{ "Asset/Sound/BGM/Title_BGM.wav"		  , true  },	// �^�C�g��BGM
		{ "Asset/Sound/BGM/StageBGM.wav"		  , true  },	// �X�e�[�WBGM
		{ "Asset/Sound/SE/�@����1 ����&�Z��.wav"  , false },	// �@��SE
		{ "Asset/Sound/SE/���n1.wav"			  , false },	// ���nSE
		{ "Asset/Sound/SE/�M�A2.wav"			  , false }		// �A�C�e���擾SE
	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SoundLabel_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SoundLabel_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SoundLabel_MAX];
	BYTE* m_DataBuffer[SoundLabel_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	void Play(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h���~����
	void Stop(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void Resume(SOUND_LABEL label);

};