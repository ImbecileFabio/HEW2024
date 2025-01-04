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

class Sound {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		//{"asset/BGM/○○○.wav", true },		// サンプルBGM（ループさせるのでtrue設定）
		//{"asset/SE /○○○.wav", false},		// サンプルSE（ループしないのでfalse設定）

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
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// 引数で指定したサウンドを再生する
	void Play(SOUND_LABEL label);

	// 引数で指定したサウンドを停止する
	void Stop(SOUND_LABEL label);

	// 引数で指定したサウンドの再生を再開する
	void Resume(SOUND_LABEL label);

};