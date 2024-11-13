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
	SoundLabelBgm000 = 0,		// ���u��BGM
//	SoundLabel������,			// ���̌`�ŗ񋓂��Ă����\��
								// ��
								// ��

	SoundLabelMax,				// �T�E���h�̑���
} SoundLabel;

class Audio
{
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR fileName;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	} Param;

	// �p�����[�^�[�\���̂̏�����
	Param param[SoundLabelMax] = {
		{ "������/������/������.wav", true },	// ���u������
		// ��
		// ��

	};	

	IXAudio2* pXAudio2 = nullptr;	// XAudio2�̃C���^�[�t�F�[�X

public:
    HRESULT Init();
	void Uninit();
	void Play(SoundLabel _label);
	void Stop(SoundLabel _label);
};

