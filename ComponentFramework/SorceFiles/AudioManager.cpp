//==================================================
// [Audio.cpp] オーディオオブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの制御をおこなうクラス
//==================================================

#include "AudioManager.h"

//--------------------------------------------------
// コンストラクタとデストラクタ
//--------------------------------------------------

AudioManager::AudioManager()
{
	// ポインタの初期化
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
// 初期化
//--------------------------------------------------

void AudioManager::Init()
{
	// COMコンポーネントの初期化
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		std::cerr << "COMの初期化に失敗しました。　エラーコード：" << hr << std::endl;
	}

	// XAudio2の初期化
	hr = XAudio2Create(&pXaudio2, 0);		// 第二引数は､デバッグモードの指定(現在は未使用なので0にする)
											// -hr = XAudio2Create(&g_pXAudio2, XAUDIO2_DEBUG_ENGINE);
	if (FAILED(hr)) {
		std::cerr << "XAudio2の初期化に失敗しました。　エラーコード：" << hr << std::endl;
		Uninit();
	}

	// マスターボイスの作成
	hr = pXaudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr)) {
		std::cerr << "マスターボイスの作成に失敗しました。　エラーコード：" << hr << std::endl;
		Uninit();
	}


	// WAVEファイルの読み込みとソースファイルの作成
	for (int SoundLabel_number = 0; SoundLabel_number < SoundLabel_MAX; SoundLabel_number++)
	{
		if (LoadWaveFile(SoundLabel_number) == -1) {		// 長くなりそうなので関数化します
			std::cerr << "WAVEファイルの読み込みに失敗しました。　エラーコード：" << hr << std::endl;
			Uninit();
		}
	}

	//完了
	std::cout << "オーディオの初期化が完了しました。";
}


//--------------------------------------------------
// 解放処理
//--------------------------------------------------

void AudioManager::Uninit()
{
	for (int SoundLabel_number = 0; SoundLabel_number < SoundLabel_MAX; SoundLabel_number++)	// ソースボイス
	{
		if (pSourceVoice[SoundLabel_number]) {
			pSourceVoice[SoundLabel_number]->DestroyVoice();
			pSourceVoice[SoundLabel_number] = nullptr;
		}
	}
	if (pMasteringVoice) {																		// マスターボイス
		pMasteringVoice->DestroyVoice();
		pMasteringVoice = nullptr;
	}		
	if (pXaudio2) {																				// Xaudio2
		pXaudio2->Release();
		pXaudio2 = nullptr;
	}
	CoUninitialize();																			// COMコンポーネント

	std::cout << "オーディオの解放が完了しました。";
}


//--------------------------------------------------
// 再生と停止
//--------------------------------------------------

void AudioManager::Play(SoundLabel _label)
{
	hr = pSourceVoice[_label]->SubmitSourceBuffer(&AudioDataBuffer);
	if (FAILED(hr)) {
		std::cerr << "オーディオデータのバッファの送信に失敗しました。　エラーコード：" << hr << std::endl;
	}
	hr = pSourceVoice[_label]->Start();
	if (FAILED(hr)) {
		std::cerr << "オーディオの再生に失敗しました。　エラーコード：" << hr << std::endl;
	}
}
void AudioManager::Stop(SoundLabel _label)
{
	hr = pSourceVoice[_label]->Stop();
	if (FAILED(hr)) {
		std::cerr << "オーディオの停止に失敗しました。　エラーコード：" << hr << std::endl;
	}
	hr = pSourceVoice[_label]->FlushSourceBuffers();
	if (FAILED(hr)) {
		std::cerr << "オーディオデータのバッファのクリアに失敗しました。　エラーコード：" << hr << std::endl;
	}
}


//--------------------------------------------------
// WAVEファイルの読み込み
//--------------------------------------------------

int AudioManager::LoadWaveFile(int _label)
{
	// WAVEファイルを開く
	if (fopen_s(&pFile, param[_label].fileName, "rb") != 0) {
		std::cerr << "WAVEファイルのオープンに失敗しました。" << std::endl;
		return -1;
	}

	// RIFFヘッダーの読み込み
	if (fread(&RiffHeader, sizeof(RiffHeader), 1, pFile) != 1) {
		std::cerr << "RIFFヘッダーの読み込みに失敗しました。" << std::endl;
		return -1;
	}

	// フォーマットチャンクの読み込み
	if (fread(&FormatChunk, sizeof(FormatChunk), 1, pFile) != 1) {
		std::cerr << "フォーマットチャンクの読み込みに失敗しました。" << std::endl;
		return -1;
	}

	// データチャンクの読み込み
	if (fread(&DataChunk, sizeof(DataChunk), 1, pFile) != 1) {
		std::cerr << "データチャンクの読み込みに失敗しました。" << std::endl;
		return -1;
	}
	pDataBuffer = (BYTE*)malloc(DataChunk.size);		// 波形データ分のメモリを確保（mallocは引数分のメモリを確保する関数）
	// 波形データの読み込み
	if (pDataBuffer == nullptr) {
		std::cerr << "バッファが初期化されていません。" << std::endl;
		return -1;
	}
	if (fread(pDataBuffer, DataChunk.size, 1, pFile) != 1) {
		std::cerr << "波形データの読み込みに失敗しました。" << std::endl;
		return -1;
	}


	// WAVEファイルのクローズ
	if (fclose(pFile) != 0) {
		std::cerr << "WAVEファイルのクローズに失敗しました。" << std::endl;
		return -1;
	}
	pFile = nullptr;


	// ソースボイスの作成
	memcpy(&WaveFormatEx, &FormatChunk.fmt, sizeof(FormatChunk.fmt));							// -波形フォーマットの設定	
	WaveFormatEx.wBitsPerSample = FormatChunk.fmt.nBlockAlign * 8 / FormatChunk.fmt.nChannels;	// -1サンプル辺りのバッファサイズを算出する
	hr = pXaudio2->CreateSourceVoice(&pSourceVoice[_label], &WaveFormatEx);						// -波形フォーマットを元にSourceVoiceの生成
	if (FAILED(hr)) {
		std::cerr << "ソースボイスの作成に失敗しました。　エラーコード：" << hr << std::endl;
		free(pDataBuffer);
		return -1;
	}

	// 再生する波形データの設定
	AudioDataBuffer.pAudioData = (BYTE*)pDataBuffer;	// -オーディオバッファへのアドレス指定
	AudioDataBuffer.Flags = XAUDIO2_END_OF_STREAM;		// -バッファの終わりを指定
	AudioDataBuffer.AudioBytes = DataChunk.size;		// -バッファのサイズ設定

	return 0;
}