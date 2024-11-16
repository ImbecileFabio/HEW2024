//==================================================
// [Audio.cpp] オーディオオブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの制御をおこなうクラス
//==================================================

#include "AudioManager.h"

//--------------------------------------------------
// 初期化
//--------------------------------------------------

HRESULT AudioManager::Init()
{
	HRESULT hr;

	// COMコンポーネントの初期化
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		std::cerr << "COMの初期化に失敗しました。　エラーコード：" << hr << std::endl;
		return hr;
	}

	// XAudio2の初期化
	hr = XAudio2Create(&pXaudio2, 0);		// 第二引数は､デバッグモードの指定(現在は未使用なので0にする)
											// -hr = XAudio2Create(&g_pXAudio2, XAUDIO2_DEBUG_ENGINE);
	if (FAILED(hr)) {
		std::cerr << "XAudio2の初期化に失敗しました。　エラーコード：" << hr << std::endl;
		Uninit();
		return hr;
	}

	// マスターボイスの作成
	hr = pXaudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr)) {
		std::cerr << "マスターボイスの作成に失敗しました。　エラーコード：" << hr << std::endl;
		Uninit();
		return hr;
	}


	// WAVEファイルの読み込み
	for (int i = 0; i < SoundLabelMAX; i++)
	{
		hr = LoadWaveFile(i);	// 長くなりそうなので関数化します
		if (FAILED(hr)) {
			std::cerr << "WAVEファイルの読み込みに失敗しました。　エラーコード：" << hr << std::endl;
			Uninit();
			return hr;
		}
	}


	//完了、戻り値を返す
	std::cout << "オーディオの初期化が完了しました。";
	return hr;
}


//--------------------------------------------------
// 解放処理
//--------------------------------------------------

void AudioManager::Uninit()
{
	if (pMasteringVoice) {					// マスターボイス
		pMasteringVoice->DestroyVoice();
		pMasteringVoice = nullptr;
	}		
	if (pXaudio2) {							// Xaudio2
		pXaudio2->Release();
		pXaudio2 = nullptr;
	}
	CoUninitialize();						// COMコンポーネント

	std::cout << "オーディオの解放が完了しました。";
}


//--------------------------------------------------
// 再生と停止
//--------------------------------------------------

void AudioManager::Play(SoundLabel _label)
{

}
void AudioManager::Stop(SoundLabel _label)
{

}


//--------------------------------------------------
// WAVEファイルの読み込み
//--------------------------------------------------

HRESULT AudioManager::LoadWaveFile(int number)
{
	HRESULT hr;

	// WAVEファイルを開く
	hr = fopen_s(&file, param[number].fileName, "rb");
	if (FAILED(hr)) {
		std::cerr << "WAVEファイルのオープンに失敗しました。　エラーコード：" << hr << std::endl;
		return hr;
	}

	// RIFFヘッダーの読み込み

	// フォーマットチャンクの読み込み

	// データチャンクの読み込み

	// WAVEファイルのクローズ
}