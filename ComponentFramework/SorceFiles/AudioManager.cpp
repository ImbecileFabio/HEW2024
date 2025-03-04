//==================================================
// [AudioManager.cpp] オーディオマネージャー
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの管理
//==================================================

#include "AudioManager.h"
#include "GameObjects/GameObject.h"
#include <iostream>
#include <cstdlib>

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//--------------------------------------------------
// コンストラクタ/デストラクタ
//--------------------------------------------------
AudioManager::AudioManager() {
	General_Init();
}

AudioManager::~AudioManager() {
	Uninit();
}

//--------------------------------------------------
// 初期化/開放処理
//--------------------------------------------------
HRESULT AudioManager::General_Init() {
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	// COM,Xaudio2,MasteringVoiceの初期化
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		std::cerr << "COM Init FAILED\n";
		Uninit();
		return -1;
	}
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr)) {
		std::cerr << "Xaudio2 Init FAILED\n";
		Uninit();
		return -1;
	}
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr)) {
		std::cerr << "MasteringVoice Init FAILED\n";
		Uninit();
		return -1;
	}

	/**** Initalize Sound ****/
	for (int i = 0; i < SoundLabel_MAX; i++)
	{
		memset(&m_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&m_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(m_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)											return HRESULT_FROM_WIN32(GetLastError());
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)	return HRESULT_FROM_WIN32(GetLastError());

		// ファイル形式とオーディオフォーマット情報の読み込み
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;
		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &m_wfx[i], dwChunkSize, dwChunkPosition);

		// オーディオデータの読み込み
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		m_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, m_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// サブミットボイスで利用するサブミットバッファの設定
		m_buffer[i].AudioBytes = dwChunkSize;
		m_buffer[i].pAudioData = m_DataBuffer[i];
		m_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		if (m_param[i].bLoop) m_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else m_buffer[i].LoopCount = 0;

		// サブミックスボイスの作成
		if (!(m_pSubmixVoice[m_param[i].soundCategory])) {
			hr = m_pXAudio2->CreateSubmixVoice(&m_pSubmixVoice[m_param[i].soundCategory], m_wfx[i].Format.nChannels, m_wfx[i].Format.nSamplesPerSec);
			if (FAILED(hr)) {
				std::cerr << "SubmixVoice Init FAILED\n";
				Uninit();
				return -1;
			}
			m_sendDescriptor[m_param[i].soundCategory].Flags = 0;
			m_sendDescriptor[m_param[i].soundCategory].pOutputVoice = m_pSubmixVoice[m_param[i].soundCategory];
			m_sendList[m_param[i].soundCategory].SendCount = 1;
			m_sendList[m_param[i].soundCategory].pSends = &m_sendDescriptor[m_param[i].soundCategory];
		}

		// ソースボイスの作成
		hr = m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(m_wfx[i].Format), 0, XAUDIO2_DEFAULT_FREQ_RATIO, nullptr, &m_sendList[m_param[i].soundCategory]);
		if (FAILED(hr)) {
			std::cerr << "SourceVoice Init FAILED\n";
			Uninit();
			return -1;
		}
	}

	return hr;
}

void AudioManager::Sound_Init(void) {

}

void AudioManager::Uninit(void) {
	for (int i = 0; i < SoundLabel_MAX; i++) {
		if (m_pSourceVoice[i]) {
			m_pSourceVoice[i]->Stop(0);
			m_pSourceVoice[i]->FlushSourceBuffers();
			m_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  m_DataBuffer[i];
		}
	}
	for (int i = 0; i < SoundCategory_MAX; i++) {
		if (m_pSubmixVoice[i]) {
			m_pSubmixVoice[i]->DestroyVoice();
		}
	}
	if (m_pMasteringVoice) m_pMasteringVoice->DestroyVoice();
	if (m_pXAudio2) m_pXAudio2->Release();
	CoUninitialize();
}


//--------------------------------------------------
// 再生/停止/再開/一時停止
//--------------------------------------------------
void AudioManager::Play(SOUND_LABEL _label) {
	HRESULT hr;
	IXAudio2SourceVoice* pSV = m_pSourceVoice[(int)_label];

	// 停止
	hr = pSV->Stop(0);
	if (FAILED(hr)) std::cerr << "AudioManager : Sound Stop FAILED";
	// ソースボイスのキューをフラッシュ
	hr = pSV->FlushSourceBuffers();
	if (FAILED(hr)) std::cerr << "AudioManager : FlushSourceBuffers FAILED";
	// ボイスキューに新しいオーディオバッファーを追加
	hr = pSV->SubmitSourceBuffer(&(m_buffer[(int)_label]));
	if (FAILED(hr)) std::cerr << "AudioManager : SubmitSourceBuffer FAILED";
	// 再生
	hr = pSV->Start(0);
	if (FAILED(hr)) std::cerr << "AudioManager : Sound Start FAILED";
}

void AudioManager::Stop(SOUND_LABEL _label) {
	HRESULT hr;
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)_label];

	if (pSV == NULL) return;

	// バッファがキューに入っていたら
	if (GetPlayingState(_label)) {
		hr = pSV->Stop(0);
		if (FAILED(hr)) std::cerr << "AudioManager : Sound Stop FAILED";
		// バッファがキューに入っていたら
		hr = pSV->FlushSourceBuffers();
		if (FAILED(hr)) std::cerr << "AudioManager : FlushSourceBuffers FAILED";
	}
}

void AudioManager::Resume(SOUND_LABEL _label) {
	IXAudio2SourceVoice* pSV = m_pSourceVoice[(int)_label];

	pSV->Start(0);
}

void AudioManager::Pause(SOUND_LABEL _label) {
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)_label];

	if (pSV == NULL) return;

	// バッファがキューに入っていたら
	if (GetPlayingState(_label)) {
		pSV->Stop(0);
	}
}


//--------------------------------------------------
// 再生状況取得
//--------------------------------------------------
bool AudioManager::GetPlayingState(SOUND_LABEL _label) {
	XAUDIO2_VOICE_STATE state;
	// ボイスの状態を取得
	m_pSourceVoice[(int)_label]->GetState(&state);
	// バッファがキューに入っていたら（再生中なら）true
	if (state.BuffersQueued > 0) {
		return true;
	}
	else {
		return false;
	}
}


//--------------------------------------------------
// 音量・再生速度設定
//--------------------------------------------------
void AudioManager::SetVolume(SOUND_LABEL _label, float _volume) {
	m_pSourceVoice[(int)_label]->SetVolume(_volume);
}

void AudioManager::SetCategoryVolume(SOUND_CATEGORY _category, float _volume) {
	m_pSubmixVoice[(int)_category]->SetVolume(_volume);
}


//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT AudioManager::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT AudioManager::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}


// 静的メンバ変数の定義
std::unique_ptr<AudioManager> AudioManager::m_instance = nullptr;