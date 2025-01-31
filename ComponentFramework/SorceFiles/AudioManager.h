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
#include <list>
#include "GameObjects/GameObject.h"

// サウンドファイル
typedef enum {
	// BGM
	SoundLabel_TitleBGM = 0,			// タイトルBGM
	SoundLabel_StageBGM,				// ステージBGM
	SoundLabel_ResultBGM,				// リザルトBGM
	// 振り子関連SE
	SoundLabel_PendulumHitSE,			// 叩くSE
	SoundLabel_PendulumCreakSE,			// 軋むSE
	// ロボット関連SE
	SoundLabel_RobotMoveSE,				// 歩行SE
	SoundLabel_RobotLandingSE,			// 着地SE
	// ステージ、リザルト関連SE
	SoundLabel_StageGearSE,				// アイテム取得SE
	SoundLabel_StageResultGearSE,		// リザルトでアイテムが嵌まる時のSE
	SoundLabel_StageRewindSteamSE,		// 巻き戻し煙SE
	// UI関連SE
	SoundLabel_UIDecisionSE,			// UIの決定とかのSE
	SoundLabel_UICancelSE,				// UIの決定とかのSE
	SoundLabel_UISceneChangeSE,			// 歯車が回るSE
	SoundLabel_UICursorMoveSE,			// カーソル移動SE
	// ギミック関連SE
	SoundLabel_GimmickLiftMoveSE0,		// リフト移動SE
	SoundLabel_GimmickLiftMoveSE1,		// リフト移動SE
	SoundLabel_GimmickLiftMoveSE2,		// リフト移動SE
	SoundLabel_GimmickLiftMoveSE3,		// リフト移動SE
	SoundLabel_GimmickLiftMoveSE4,		// リフト移動SE
	SoundLabel_GimmickWeakFloorStaySE0,	// 弱い床の待機SE
	SoundLabel_GimmickWeakFloorStaySE1,	// 弱い床の待機SE
	SoundLabel_GimmickWeakFloorStaySE2,	// 弱い床の待機SE
	SoundLabel_GimmickWeakFloorStaySE3,	// 弱い床の待機SE
	SoundLabel_GimmickWeakFloorStaySE4,	// 弱い床の待機SE
	SoundLabel_GimmickWeakFloorDropSE,	// 弱い床の落下SE
	SoundLabel_GimmickSmokeSE0,			// 煙SE
	SoundLabel_GimmickSmokeSE1,			// 煙SE
	SoundLabel_GimmickSmokeSE2,			// 煙SE
	SoundLabel_GimmickSmokeSE3,			// 煙SE
	SoundLabel_GimmickSmokeSE4,			// 煙SE

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
		{ "Asset/Sound/BGM/TitleBGM.wav",				true,  BGM },	// 0.タイトルBGM
		{ "Asset/Sound/BGM/StageBGM1.1.wav",			true,  BGM },	// 1.ステージBGM
		{ "Asset/Sound/BGM/ResultBGM.wav",				true,  BGM },	// 2.リザルトBGM
		// 振り子関連SE
		{ "Asset/Sound/SE/PendulumHit.wav",				false, SE },	// 3.叩くSE
		{ "Asset/Sound/SE/PendulumCreak.wav",			false, SE },	// 4.軋むSE
		// ロボット関連SE
		{ "Asset/Sound/SE/RobotMove.wav",				false, SE },	// 5.歩行SE
		{ "Asset/Sound/SE/RobotLanding1.1.wav",			false, SE },	// 6.着地SE
		// ステージ、リザルト関連SE
		{ "Asset/Sound/SE/StageGear1.1.wav",			false, SE },	// 7.アイテム取得SE
		{ "Asset/Sound/SE/StageResultGear.wav",			false, SE },	// 8.リザルトでアイテムが嵌まる時のSE
		{ "Asset/Sound/SE/StageRewindSmoke.wav",		false, SE },	// 9.巻き戻し煙SE
		// UI関連SE
		{ "Asset/Sound/SE/UIDecision.wav",				false, SE },	// 10.UIの決定とかのSE
		{ "Asset/Sound/SE/UICancel.wav",				false, SE },	// 11.UIの決定とかのSE
		{ "Asset/Sound/SE/UISceneChange.wav",			false, SE },	// 12.歯車が回るSE
		{ "Asset/Sound/SE/UICursorMove.wav",			false, SE },	// 13.カーソル移動SE
		// ギミック関連SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.リフト移動SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.リフト移動SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.リフト移動SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.リフト移動SE
		{ "Asset/Sound/SE/GimmickLiftMove1.1.wav",		false, SE },	// 14.リフト移動SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.弱い床の待機SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.弱い床の待機SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.弱い床の待機SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.弱い床の待機SE
		{ "Asset/Sound/SE/GimmickWeakFloorStay.wav",	false, SE },	// 15.弱い床の待機SE
		{ "Asset/Sound/SE/GimmickWeakFloorDrop1.1.wav",	false, SE },	// 16.弱い床の落下SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.煙SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.煙SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.煙SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.煙SE
		{ "Asset/Sound/SE/GimmickSmoke1.wav",			false, SE },	// 17.煙SE

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
	void Play(GameObject::TypeID _id, int _fier);
	void Stop(SOUND_LABEL _label);
	void Stop(GameObject::TypeID _id, int _fier);
	void Resume(SOUND_LABEL _label);
	void Pause(SOUND_LABEL _label);

	void SetVolume(SOUND_LABEL _label, float _volume);
	void SetCategoryVolume(SOUND_CATEGORY _category, float _volume);

	bool GetPlayingState(SOUND_LABEL _label);
	bool GetPlayingState(GameObject::TypeID _id, int _fier);
};