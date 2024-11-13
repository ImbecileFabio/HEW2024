//==================================================
// [Audio.cpp] �I�[�f�B�I�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�T�E���h�̐���������Ȃ��N���X
//==================================================

#include "AudioManager.h"

//--------------------------------------------------
// ������
//--------------------------------------------------

HRESULT AudioManager::Init()
{
	HRESULT hr;

	// COM�R���|�[�l���g�̏�����
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		std::cerr << "COM�̏������Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
		return -1;
	}

	// XAudio2�̏�����
	hr = XAudio2Create(&pXaudio2, 0);		// �������ͤ�f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
											// -hr = XAudio2Create(&g_pXAudio2, XAUDIO2_DEBUG_ENGINE);
	if (FAILED(hr)) {
		std::cerr << "XAudio2�̏������Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
		CoUninitialize();
		return -1;
	}

	// �}�X�^�[�{�C�X�̍쐬
	hr = pXaudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr)) {
		std::cerr << "�}�X�^�[�{�C�X�̍쐬�Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
		if (pXaudio2)	pXaudio2->Release();
		CoUninitialize();
		return -1;
	}

	// �T�u�~�b�N�X�{�C�X�̍쐬�H�b�����u

	//�����A�߂�l��Ԃ�
	std::cout << "�I�[�f�B�I�̏��������������܂����B";
	return hr;
}

//--------------------------------------------------
// �������
//--------------------------------------------------

void AudioManager::Uninit()
{
	if (pMasteringVoice) {					// �}�X�^�[�{�C�X
		pMasteringVoice->DestroyVoice();
		pMasteringVoice = nullptr;
	}		
	if (pXaudio2) {							// Xaudio2
		pXaudio2->Release();
		pXaudio2 = nullptr;
	}
	CoUninitialize();						// COM�R���|�[�l���g

	std::cout << "�I�[�f�B�I�̉�����������܂����B";
}

void AudioManager::Play(SoundLabel _label)
{

}

void AudioManager::Stop(SoundLabel _label)
{

}