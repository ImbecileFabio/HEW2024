//==================================================
// [Audio.h] �I�[�f�B�I�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�T�E���h�̐���������Ȃ��N���X
//==================================================
#pragma once
#include <xaudio2.h>
#include <iostream>

// �T�E���h�t�@�C��
typedef enum
{
	SoundLabelBGM001 = 0,		// ���u��BGM
//	SoundLabel������,				// ���̌`�ŗ񋓂��Ă����\��
								// ��
								// ��

	SoundLabelMAX,				// �T�E���h�̑���
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
	Param param[SoundLabelMAX] = {
		{ "../Asset/Sound/BGM/Devine-Fencer.wav", true },	// ���u������
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

	IXAudio2*				pXaudio2		= nullptr;		// -XAudio2�̃|�C���^
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;		// -�}�X�^�[�{�C�X�̃|�C���^
    IXAudio2SourceVoice*	pSourceVoice[SoundLabelMAX];	// -�\�[�X�{�C�X�̃|�C���^�i�T�E���h���������j
	FILE*		file = nullptr;	// -�t�@�C���̃|�C���^
	RiffHeader	riffHeader;		// -RIFF�w�b�_�[
	FormatChunk	formatChunk;	// -�t�H�[�}�b�g�`�����N
	Chunk		dataChunk;		// -�f�[�^�`�����N	�i"���ʎq�iID�j" "�`�����N�̃T�C�Y"�j
	BYTE*		pData;			// -�g�`�f�[�^		�i"�f�[�^�̓��e"�j

public:
    HRESULT Init();
	void Uninit();
	void Play(SoundLabel _label);
	void Stop(SoundLabel _label);
	HRESULT LoadWaveFile(int number);
};