//==================================================
// [Audio.h] オーディオオブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの制御をおこなうクラス
// 　　　Init()で初期化、
//		Uninit()で解放、
// 　　　Play()で再生、
//		Stop()で停止を行う。
//==================================================
#pragma once
#include <xaudio2.h>
#include <iostream>

// サウンドファイル
typedef enum
{
	SoundLabel_SampleBGM = 0,	// サンプルBGM
	SoundLabel_SampleSE,		// サンプルSE
//	SoundLabel○○○,				// この形で列挙していく予定
								// ↓
								// ↓

	SoundLabel_MAX,				// サウンドの総数
} SoundLabel;

class AudioManager
{
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR fileName;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} Param;

	// パラメーター構造体の初期化
	Param param[SoundLabel_MAX] = {
		{ "../Asset/Sound/BGM/Devine-Fencer.wav", true  },	// サンプルBGM音源
		{ "../Asset/Sound/SE /SE33.wav"			, false },	// サンプルSE音源
		// ↓
		// ↓

	};	
	
	// -チャンクは "識別子（ID）" "チャンクのサイズ"　"データの内容"　の3つで構成されている
	// -そのうち形式が共有の "識別子（ID）" "チャンクのサイズ" を基本構造としてまとめている
	// チャンクデータの基本構造 
	struct Chunk		// -（そもそものチャンクというものの定義） 
	{
		char	id[4]; // チャンク毎のID
		int32_t	size;  // チャンクサイズ
	};

	// RIFFヘッダー
	// -（WAVEファイル全体を構成する一番外側のチャンク）(この中に "波形のフォーマットチャンク" と "波形データ本体チャンク" が入る)
	struct RiffHeader
	{
		Chunk	chunk;   // ?"RIFF"
		char	type[4]; // ?"WAVE"
	};

	// FMTチャンク
	// -（波形のフォーマットを記述するチャンク）
	struct FormatChunk
	{
		Chunk		chunk; // ?"fmt "
		WAVEFORMAT	fmt;   // 波形フォーマット
	};

	HRESULT hr;		// -エラーチェック用の変数
	IXAudio2*				pXaudio2		= nullptr;		// -XAudio2のポインタ
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;		// -マスターボイスのポインタ
    IXAudio2SourceVoice*	pSourceVoice[SoundLabel_MAX];	// -ソースボイスのポインタ（サウンド数分生成）
	FILE*			pFile = nullptr;	// -ファイルのポインタ
	RiffHeader		riffHeader;			// -RIFFヘッダー
	FormatChunk		formatChunk;		// -フォーマットチャンク
	Chunk			dataChunk;			// -データチャンク	（"識別子（ID）" "チャンクのサイズ"）
	BYTE*			pDataBuffer;		// -波形データ		（"データの内容"）
	XAUDIO2_BUFFER	audioDataBuffer{};	// -オーディオデータを再生するために使用するバッファ

public:
    void Init();
	void Uninit();
	void Play(SoundLabel _label);
	void Stop(SoundLabel _label);
	int LoadWaveFile(int number);	// waveファイルの読み込み
};