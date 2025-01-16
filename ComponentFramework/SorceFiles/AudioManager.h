//==================================================
// [AudioManager.h] オーディオマネージャー
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの管理
//==================================================

#pragma once
#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	SoundLabel_TitleBGM = 0,		// タイトルBGM
	SoundLabel_StageBGM,			// ステージBGM
	SoundLabel_HitSE,				// 叩くSE
	SoundLabel_LandingSE,			// 着地SE
	SoundLabel_ItemGet,				// アイテム取得SE

	SoundLabel_MAX,
} SOUND_LABEL;

class AudioManager {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		{ "Asset/Sound/BGM/Title_BGM.wav"		  , true  },	// タイトルBGM
		{ "Asset/Sound/BGM/StageBGM.wav"		  , true  },	// ステージBGM
		{ "Asset/Sound/SE/叩く音1 下げ&短く.wav"  , false },	// 叩くSE
		{ "Asset/Sound/SE/着地1.wav"			  , false },	// 着地SE
		{ "Asset/Sound/SE/ギア2.wav"			  , false }		// アイテム取得SE
	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SoundLabel_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SoundLabel_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SoundLabel_MAX];
	BYTE* m_DataBuffer[SoundLabel_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	HRESULT Init(void);
	void Uninit(void);

	void Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Resume(SOUND_LABEL label);
};
