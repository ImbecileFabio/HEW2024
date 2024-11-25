//==================================================
// [Audio.cpp] �I�[�f�B�I�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�T�E���h�̐���������Ȃ��N���X
//==================================================

#include "AudioManager.h"

//--------------------------------------------------
// �R���X�g���N�^�ƃf�X�g���N�^
//--------------------------------------------------

AudioManager::AudioManager()
{
	// �|�C���^�̏�����
	pXaudio2		= nullptr;
	pMasteringVoice	= nullptr;
	pFile			= nullptr;
	Init();
}
AudioManager::~AudioManager()
{
	Uninit();
}

//--------------------------------------------------
// ������
//--------------------------------------------------

void AudioManager::Init()
{
	// COM�R���|�[�l���g�̏�����
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		std::cerr << "COM�̏������Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
	}

	// XAudio2�̏�����
	hr = XAudio2Create(&pXaudio2, 0);		// �������ͤ�f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
											// -hr = XAudio2Create(&g_pXAudio2, XAUDIO2_DEBUG_ENGINE);
	if (FAILED(hr)) {
		std::cerr << "XAudio2�̏������Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
		Uninit();
	}

	// �}�X�^�[�{�C�X�̍쐬
	hr = pXaudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr)) {
		std::cerr << "�}�X�^�[�{�C�X�̍쐬�Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
		Uninit();
	}


	// WAVE�t�@�C���̓ǂݍ��݂ƃ\�[�X�t�@�C���̍쐬
	for (int SoundLabel_number = 0; SoundLabel_number < SoundLabel_MAX; SoundLabel_number++)
	{
		if (LoadWaveFile(SoundLabel_number) == -1) {		// �����Ȃ肻���Ȃ̂Ŋ֐������܂�
			std::cerr << "WAVE�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
			Uninit();
		}
	}

	//����
	std::cout << "�I�[�f�B�I�̏��������������܂����B";
}


//--------------------------------------------------
// �������
//--------------------------------------------------

void AudioManager::Uninit()
{
	for (int SoundLabel_number = 0; SoundLabel_number < SoundLabel_MAX; SoundLabel_number++)	// �\�[�X�{�C�X
	{
		if (pSourceVoice[SoundLabel_number]) {
			pSourceVoice[SoundLabel_number]->DestroyVoice();
			pSourceVoice[SoundLabel_number] = nullptr;
		}
	}
	if (pMasteringVoice) {																		// �}�X�^�[�{�C�X
		pMasteringVoice->DestroyVoice();
		pMasteringVoice = nullptr;
	}		
	if (pXaudio2) {																				// Xaudio2
		pXaudio2->Release();
		pXaudio2 = nullptr;
	}
	CoUninitialize();																			// COM�R���|�[�l���g

	std::cout << "�I�[�f�B�I�̉�����������܂����B";
}


//--------------------------------------------------
// �Đ��ƒ�~
//--------------------------------------------------

void AudioManager::Play(SoundLabel _label)
{
	hr = pSourceVoice[_label]->SubmitSourceBuffer(&AudioDataBuffer);
	if (FAILED(hr)) {
		std::cerr << "�I�[�f�B�I�f�[�^�̃o�b�t�@�̑��M�Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
	}
	hr = pSourceVoice[_label]->Start();
	if (FAILED(hr)) {
		std::cerr << "�I�[�f�B�I�̍Đ��Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
	}
}
void AudioManager::Stop(SoundLabel _label)
{
	hr = pSourceVoice[_label]->Stop();
	if (FAILED(hr)) {
		std::cerr << "�I�[�f�B�I�̒�~�Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
	}
	hr = pSourceVoice[_label]->FlushSourceBuffers();
	if (FAILED(hr)) {
		std::cerr << "�I�[�f�B�I�f�[�^�̃o�b�t�@�̃N���A�Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
	}
}


//--------------------------------------------------
// WAVE�t�@�C���̓ǂݍ���
//--------------------------------------------------

int AudioManager::LoadWaveFile(int _label)
{
	// WAVE�t�@�C�����J��
	if (fopen_s(&pFile, param[_label].fileName, "rb") != 0) {
		std::cerr << "WAVE�t�@�C���̃I�[�v���Ɏ��s���܂����B" << std::endl;
		return -1;
	}

	// RIFF�w�b�_�[�̓ǂݍ���
	if (fread(&RiffHeader, sizeof(RiffHeader), 1, pFile) != 1) {
		std::cerr << "RIFF�w�b�_�[�̓ǂݍ��݂Ɏ��s���܂����B" << std::endl;
		return -1;
	}

	// �t�H�[�}�b�g�`�����N�̓ǂݍ���
	if (fread(&FormatChunk, sizeof(FormatChunk), 1, pFile) != 1) {
		std::cerr << "�t�H�[�}�b�g�`�����N�̓ǂݍ��݂Ɏ��s���܂����B" << std::endl;
		return -1;
	}

	// �f�[�^�`�����N�̓ǂݍ���
	if (fread(&DataChunk, sizeof(DataChunk), 1, pFile) != 1) {
		std::cerr << "�f�[�^�`�����N�̓ǂݍ��݂Ɏ��s���܂����B" << std::endl;
		return -1;
	}
	pDataBuffer = (BYTE*)malloc(DataChunk.size);		// �g�`�f�[�^���̃��������m�ہimalloc�͈������̃��������m�ۂ���֐��j
	// �g�`�f�[�^�̓ǂݍ���
	if (pDataBuffer == nullptr) {
		std::cerr << "�o�b�t�@������������Ă��܂���B" << std::endl;
		return -1;
	}
	if (fread(pDataBuffer, DataChunk.size, 1, pFile) != 1) {
		std::cerr << "�g�`�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B" << std::endl;
		return -1;
	}


	// WAVE�t�@�C���̃N���[�Y
	if (fclose(pFile) != 0) {
		std::cerr << "WAVE�t�@�C���̃N���[�Y�Ɏ��s���܂����B" << std::endl;
		return -1;
	}
	pFile = nullptr;


	// �\�[�X�{�C�X�̍쐬
	memcpy(&WaveFormatEx, &FormatChunk.fmt, sizeof(FormatChunk.fmt));							// -�g�`�t�H�[�}�b�g�̐ݒ�	
	WaveFormatEx.wBitsPerSample = FormatChunk.fmt.nBlockAlign * 8 / FormatChunk.fmt.nChannels;	// -1�T���v���ӂ�̃o�b�t�@�T�C�Y���Z�o����
	hr = pXaudio2->CreateSourceVoice(&pSourceVoice[_label], &WaveFormatEx);						// -�g�`�t�H�[�}�b�g������SourceVoice�̐���
	if (FAILED(hr)) {
		std::cerr << "�\�[�X�{�C�X�̍쐬�Ɏ��s���܂����B�@�G���[�R�[�h�F" << hr << std::endl;
		free(pDataBuffer);
		return -1;
	}

	// �Đ�����g�`�f�[�^�̐ݒ�
	AudioDataBuffer.pAudioData = (BYTE*)pDataBuffer;	// -�I�[�f�B�I�o�b�t�@�ւ̃A�h���X�w��
	AudioDataBuffer.Flags = XAUDIO2_END_OF_STREAM;		// -�o�b�t�@�̏I�����w��
	AudioDataBuffer.AudioBytes = DataChunk.size;		// -�o�b�t�@�̃T�C�Y�ݒ�

	return 0;
}