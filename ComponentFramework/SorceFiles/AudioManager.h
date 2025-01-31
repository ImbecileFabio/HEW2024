//==================================================
// [AudioManager.h] オーディオマネージャー
// 著者：中谷凌也
//--------------------------------------------------
// 説明：サウンドの管理
// 
// 機能：GetInstance()			インスタンスの取得	
// 		
//		Play(サウンドラベル)	サウンドの再生
//		Stop(サウンドラベル)	サウンドの停止
//		Resume(サウンドラベル)	サウンドの再開
// 
// 		SetVolume(サウンドラベル, 0.0f～1.0fの数値)			ボリュームの設定
//		SetCategoryVolume(サウンドカテゴリ, 0.0f～1.0fの数値)	カテゴリ毎のボリュームの設定
// 
// 		GetPlayingState(サウンドラベル)	サウンドの再生状態の取得
//==================================================

#pragma once
#include <xaudio2.h>
#include <iostream>
#include <memory>

// サウンドファイル
typedef enum {
	// BGM
	SoundLabel_TitleBGM = 0,		// タイトルBGM
	SoundLabel_StageBGM,			// ステージBGM
	SoundLabel_ResultBGM,			// リザルトBGM
	// 振り子関連SE
	SoundLabel_PendulumHitSE,		// 叩くSE
	SoundLabel_PendulumCreakSE,		// 軋むSE
	// ロボット関連SE
	SoundLabel_RobotMoveSE,			// 歩行SE
	SoundLabel_RobotLandingSE,		// 着地SE
	// ステージ、リザルト関連SE
	SoundLabel_StageGearSE,			// アイテム取得SE
	SoundLabel_StageResultGearSE,	// リザルトでアイテムが嵌まる時のSE
	SoundLabel_StageRewindSteamSE,	// 巻き戻し煙SE
	// ギミック関連SE
	SoundLabel_GimmickLiftMove,		// リフト移動SE
	SoundLabel_GimmickWeakFloorStay,// 弱い床の待機SE
	// UI関連SE
	SoundLabel_UIDecisionSE,		// UIの決定とかのSE
	SoundLabel_UICancelSE,			// UIの決定とかのSE
	SoundLabel_UISceneChangeSE,		// 歯車が回るSE
	SoundLabel_UICursorMoveSE,		// カーソル移動SE

	SoundLabel_MAX,
} SOUND_LABEL;
typedef enum {
	BGM = 0,
	SE,

	SoundCategory_MAX
}SOUND_CATEGORY;

class AudioManager {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;				// 音声ファイルまでのパスを設定
		bool bLoop;						// trueでループ。通常、BGMはture、SEはfalse。
		SOUND_CATEGORY soundCategory;	// BGMかSEどちらのサブミックスボイスを適用するかの識別子
	} PARAM;

	PARAM m_param[SoundLabel_MAX] =
	{
		// BGM
		{ "Asset/Sound/BGM/TitleBGM.wav",				true,  BGM },	// タイトルBGM
		{ "Asset/Sound/BGM/StageBGM1.1.wav",			true,  BGM },	// ステージBGM
		{ "Asset/Sound/BGM/ResultBGM.wav",				true,  BGM },	// リザルトBGM
		// 振り子関連SE
		{ "Asset/Sound/SE/PendulumHit.wav",				false, SE },	// 叩くSE
		{ "Asset/Sound/SE/PendulumCreak.wav",			false, SE },	// 軋むSE
		// ロボット関連SE
		{ "Asset/Sound/SE/RobotMove.wav",				false, SE },	// 歩行SE
		{ "Asset/Sound/SE/RobotLanding1.1.wav",			false, SE },	// 着地SE
		// ステージ、リザルト関連SE
		{ "Asset/Sound/SE/StageGear1.1.wav",			false, SE },	// アイテム取得SE
		{ "Asset/Sound/SE/StageResultGear.wav",			false, SE },	// リザルトでアイテムが嵌まる時のSE
		{ "Asset/Sound/SE/StageRewindSmoke.wav",		false, SE },	// 巻き戻し煙SE
		// ギミック関連SE
		{ "Asset/Sound/SE/GimmickLiftMove.wav",			false, SE },	// リフト移動SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 弱い床の待機SE
		// UI関連SE
		{ "Asset/Sound/SE/UIDecision.wav",				false, SE },	// UIの決定とかのSE
		{ "Asset/Sound/SE/UICancel.wav",				false, SE },	// UIの決定とかのSE
		{ "Asset/Sound/SE/UISceneChange.wav",			false, SE },	// 歯車が回るSE
		{ "Asset/Sound/SE/UICursorMove.wav",			false, SE },	// カーソル移動SE

	};

	IXAudio2* m_pXAudio2 = nullptr;
	IXAudio2MasteringVoice* m_pMasteringVoice = nullptr;
	IXAudio2SubmixVoice* m_pSubmixVoice[SoundCategory_MAX] = { nullptr };
	IXAudio2SourceVoice* m_pSourceVoice[SoundLabel_MAX] = { nullptr };
	WAVEFORMATEXTENSIBLE m_wfx[SoundLabel_MAX] = {}; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SoundLabel_MAX] = {};
	BYTE* m_DataBuffer[SoundLabel_MAX] = { nullptr };
	XAUDIO2_SEND_DESCRIPTOR m_sendDescriptor[SoundCategory_MAX] = {};
	XAUDIO2_VOICE_SENDS m_sendList[SoundCategory_MAX] = {};

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	static std::unique_ptr<AudioManager> m_instance;
public:
	AudioManager();
	~AudioManager();

	static std::unique_ptr<AudioManager>& GetInstance() {
		if (!m_instance) m_instance = std::make_unique<AudioManager>();
		return m_instance;
	}

	HRESULT General_Init(void);
	void Sound_Init(void);
	void Uninit(void);

	void Play(SOUND_LABEL _label);
	void Stop(SOUND_LABEL _label);
	void Resume(SOUND_LABEL _label);

	void SetVolume(SOUND_LABEL _label, float _volume);
	void SetCategoryVolume(SOUND_CATEGORY _category, float _volume);

	bool GetPlayingState(SOUND_LABEL _label);
};