//==================================================
// [PemdulumManager.cpp] 
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の管理（選択）
//==================================================

#include "PemdulumManager.h"
#include "GameManager.h"
#include "GameObjects/GameObject.h"
#include "InputManager.h"

//--------------------------------------------------
// コンストラクタ・デストラクタ
//--------------------------------------------------
PemdulumManager::PemdulumManager(){
	Init();
}
PemdulumManager::~PemdulumManager(){
	Uninit();
}

//--------------------------------------------------
// 初期化処理・終了処理・更新処理
//--------------------------------------------------
void PemdulumManager::Init(){
	// 振り子の検索、確保
	for (GameObject* object : GameManager::GetGameObjects()) {
		if (object->GetType() == "Pendulum")
		pemgulumList_.push_back(object);
	}
	pSelectedPemdulum = pemgulumList_.front();

	// 振り子の動作、長さの状態
	langthState_ = LangthState::normalLangth;
	pemdulumMovement_ = false;
}
void PemdulumManager::Uninit() {
	pemgulumList_.clear();
	pSelectedPemdulum = nullptr;

}
void PemdulumManager::Update(){
	// if(スティックの入力){
	//	pSelectedPemdulum = 内積が一定以内かつ最も近いオブジェクトのポインタを返す関数
	// }
	PemdulumMovementChange();
	PemgulumLangthChange();
}

//--------------------------------------------------
// 内積が一定以内かつ最も近いオブジェクトのポインタを返す（選択）
//--------------------------------------------------
GameObject* PemdulumManager::PemgulumSelect(float _inputStick) {
	if (InputManager::GetLeftAnalogStick()) {
		for (auto& pemdulum : pemgulumList_) {
			if (pSelectedPemdulum != pemdulum) {
				pemdulumPosition_= pemdulum->GetComponent<TransformComponent>()->GetPosition();
			}
		}
	}
}

//--------------------------------------------------
// 振り子の状態変異
//--------------------------------------------------
void PemdulumManager::PemdulumMovementChange() {
	// Aボタン（動作の変更）
	if (InputManager::GetButtonTrigger(XINPUT_A)) {
		if (pemdulumMovement_) {
			pemdulumMovement_ = !pemdulumMovement_;
		} else {
			pemdulumMovement_ = !pemdulumMovement_;
		}
	}
}

//--------------------------------------------------
// 長さの変更
//--------------------------------------------------
void PemdulumManager::PemgulumLangthChange() {
	// 十字↑（短くする）
	if (InputManager::GetButtonTrigger(XINPUT_UP)) {
		if (langthState_ != LangthState::shortLangth) {
			langthState_ -= LangthChange;
		} else {
			// 処理をしない
		}
	}
	// 十字↓（長くする）
	if (InputManager::GetButtonTrigger(XINPUT_DOWN)) {
		if (langthState_ != LangthState::longLangth) {
			langthState_ += LangthChange;
		} else {
			// 処理をしない
		}
	}
}