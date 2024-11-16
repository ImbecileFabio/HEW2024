//==================================================
// [Audio.h] オーディオオブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの制御をおこなうクラス
//==================================================
#pragma once
#include <xaudio2.h>
#include <iostream>

// サウンドファイル
typedef enum
{
	SoundLabelBGM001 = 0,		// 仮置きBGM
//	SoundLabel○○○,				// この形で列挙していく予定
								// ↓
								// ↓

	SoundLabelMAX,				// サウンドの総数
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
	Param param[SoundLabelMAX] = {
		{ "../Asset/Sound/BGM/Devine-Fencer.wav", true },	// 仮置き音源
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

	IXAudio2*				pXaudio2		= nullptr;		// -XAudio2のポインタ
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;		// -マスターボイスのポインタ
    IXAudio2SourceVoice*	pSourceVoice[SoundLabelMAX];	// -ソースボイスのポインタ（サウンド数分生成）
	FILE*		file = nullptr;	// -ファイルのポインタ
	RiffHeader	riffHeader;		// -RIFFヘッダー
	FormatChunk	formatChunk;	// -フォーマットチャンク
	Chunk		dataChunk;		// -データチャンク	（"識別子（ID）" "チャンクのサイズ"）
	BYTE*		pData;			// -波形データ		（"データの内容"）

public:
    HRESULT Init();
	void Uninit();
	void Play(SoundLabel _label);
	void Stop(SoundLabel _label);
	HRESULT LoadWaveFile(int number);
};