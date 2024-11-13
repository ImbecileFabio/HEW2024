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
	SoundLabelBgm000 = 0,		// 仮置きBGM
//	SoundLabel○○○,			// この形で列挙していく予定
								// ↓
								// ↓

	SoundLabelMax,				// サウンドの総数
} SoundLabel;

class Audio
{
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR fileName;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} Param;

	// パラメーター構造体の初期化
	Param param[SoundLabelMax] = {
		{ "○○○/○○○/○○○.wav", true },	// 仮置き音源
		// ↓
		// ↓

	};	

	IXAudio2* pXAudio2 = nullptr;	// XAudio2のインターフェース

public:
    HRESULT Init();
	void Uninit();
	void Play(SoundLabel _label);
	void Stop(SoundLabel _label);
};

