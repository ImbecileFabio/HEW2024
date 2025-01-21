//==================================================
// [AudioManager.h] オーディオマネージャー
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの管理
// 
// 機能：	Init()	初期化
//		Uninit()	解放		
// 		
//		Play(サウンドラベル)	サウンドの再生
//		Stop(サウンドラベル)	サウンドの停止
//		Resume(サウンドラベル)	サウンドの再開
// 
// 		SetVolume(サウンドラベル, 0.0f～1.0fの数値)			ボリュームの設定
//		SetCategoryVolume(サウンドカテゴリ, 0.0f～1.0fの数値)	カテゴリ毎のボリュームの設定
//==================================================

#pragma once
#include <xaudio2.h>

// サウンドファイル
typedef enum {
	SoundLabel_TitleBGM = 0,		// タイトルBGM
	SoundLabel_StageBGM,			// ステージBGM
	SoundLabel_HitSE,				// 叩くSE
	SoundLabel_LandingSE,			// 着地SE
	SoundLabel_ItemGet,				// アイテム取得SE

	SoundLabel_MAX,
} SOUND_LABEL;
typedef enum {
	BGM = 0,
	SE,

	SoundTag_MAX
}SOUND_CATEGORY;

class AudioManager {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
		SOUND_CATEGORY soundCategory;	// BGMかSEどちらのサブミックスボイスを適用するかの識別子
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		{ "Asset/Sound/BGM/Title_BGM.wav",	true,  BGM },	// タイトルBGM
		{ "Asset/Sound/BGM/StageBGM.wav",	true,  BGM },	// ステージBGM
		{ "Asset/Sound/SE/叩く音.wav",		false, SE },	// 叩くSE
		{ "Asset/Sound/SE/着地1.wav",		false, SE },	// 着地SE
		{ "Asset/Sound/SE/ギア獲得.wav",	false, SE }		// アイテム取得SE
	};

	IXAudio2* m_pXAudio2 = nullptr;
	IXAudio2MasteringVoice* m_pMasteringVoice = nullptr;
	IXAudio2SubmixVoice* m_pSubmixVoice[SoundTag_MAX];
	IXAudio2SourceVoice* m_pSourceVoice[SoundLabel_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SoundLabel_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SoundLabel_MAX];
	BYTE* m_DataBuffer[SoundLabel_MAX];
	XAUDIO2_SEND_DESCRIPTOR m_sendDescriptor[SoundTag_MAX];
	XAUDIO2_VOICE_SENDS m_sendList[SoundTag_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	HRESULT Init(void);
	void Uninit(void);

	void Play(SOUND_LABEL _label);
	void Stop(SOUND_LABEL _label);
	void Resume(SOUND_LABEL _label);

	void SetVolume(SOUND_LABEL _label, float _volume);
	void SetCategoryVolume(SOUND_CATEGORY _category, float _volume);
	void SetSpeed(SOUND_LABEL _label, float _spped);
};
