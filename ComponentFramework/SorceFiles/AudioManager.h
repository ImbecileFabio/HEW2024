//==================================================
// [Audio.h] �I�[�f�B�I�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�T�E���h�̐���������Ȃ��N���X
// �@�@�@Init()�ŏ������A
//		Uninit()�ŉ���A
// �@�@�@Play(�T�E���h���x��)�ōĐ��A
//		Stop(�T�E���h���x��)�Œ�~���s���B
//==================================================
#pragma once
#include <xaudio2.h>
#include <iostream>

// �T�E���h�t�@�C���̃��x��
typedef enum
{
	SoundLabel_SampleBGM = 0,	// �T���v��BGM
	SoundLabel_SampleSE,		// �T���v��SE
	SoundLabel_TitleBGM,		// �^�C�g��BGM
//	SoundLabel������,			// ���̌`�ŗ񋓂��Ă����\��

	SoundLabel_MAX,				// �T�E���h�̑���
} SoundLabel;

class AudioManager
{
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR fileName;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	} Param;

	// �p�����[�^�[�\���̂̏�����
	Param param[SoundLabel_MAX] = {
		{ "../Asset/Sound/BGM/Devine-Fencer.wav", true  },	// �T���v��BGM����
		{ "../Asset/Sound/SE/SE33.wav"			, false },	// �T���v��SE����

		{"../Asset/Sound/BGM/Title_BGM.wav", true}			// �^�C�g��BGM
		// ��
		// ��
	};	
	
	// -�`�����N�� "���ʎq�iID�j" "�`�����N�̃T�C�Y"�@"�f�[�^�̓��e"�@��3�ō\������Ă���
	// -���̂����`�������L�� "���ʎq�iID�j" "�`�����N�̃T�C�Y" ����{�\���Ƃ��Ă܂Ƃ߂Ă���
	// �`�����N�f�[�^�̊�{�\�� 
	struct Chunk		// -�i���������̃`�����N�Ƃ������̂̒�`�j 
	{
		char	id[4]; // �`�����N����ID
		int32_t	size;  // �`�����N�T�C�Y
	};

	// RIFF�w�b�_�[
	// -�iWAVE�t�@�C���S�̂��\�������ԊO���̃`�����N�j(���̒��� "�g�`�̃t�H�[�}�b�g�`�����N" �� "�g�`�f�[�^�{�̃`�����N" ������)
	struct RiffHeader
	{
		Chunk	chunk;   // ?"RIFF"
		char	type[4]; // ?"WAVE"
	};

	// FMT�`�����N
	// -�i�g�`�̃t�H�[�}�b�g���L�q����`�����N�j
	struct FormatChunk
	{
		Chunk		chunk; // ?"fmt "
		WAVEFORMAT	fmt;   // �g�`�t�H�[�}�b�g
	};

	HRESULT hr;		// -�G���[�`�F�b�N�p�̕ϐ�
	IXAudio2*				pXaudio2;						// -XAudio2�̃|�C���^
	IXAudio2MasteringVoice* pMasteringVoice;				// -�}�X�^�[�{�C�X�̃|�C���^
    IXAudio2SourceVoice*	pSourceVoice[SoundLabel_MAX];	// -�\�[�X�{�C�X�̃|�C���^�i�T�E���h���������j
	FILE*			pFile;				// -�t�@�C���̃|�C���^
	RiffHeader		RiffHeader;			// -RIFF�w�b�_�[
	FormatChunk		FormatChunk;		// -�t�H�[�}�b�g�`�����N
	Chunk			DataChunk;			// -�f�[�^�`�����N	�i"���ʎq�iID�j" "�`�����N�̃T�C�Y"�j
	BYTE*			pDataBuffer;		// -�g�`�f�[�^		�i"�f�[�^�̓��e"�j
	XAUDIO2_BUFFER	AudioDataBuffer{};	// -�I�[�f�B�I�f�[�^���Đ����邽�߂Ɏg�p����o�b�t�@
	WAVEFORMATEX	WaveFormatEx{};		// -�g�`�t�H�[�}�b�g�\����


public:
	 AudioManager();
	~AudioManager();
    void Init();
	void Uninit();
	void Play(SoundLabel _label);
	void Stop(SoundLabel _label);
	int LoadWaveFile(int _label);	// wave�t�@�C���̓ǂݍ���
};