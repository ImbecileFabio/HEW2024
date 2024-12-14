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
	GM = new GameManager;
	// 振り子の検索、確保
	for (GameObject* object : GM->GetGameObjects()) {
		if (object->GetType() == GameObject::TypeID::Pendulum)
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
	PemgulumSelect();
	PemdulumMovementChange();
	PemgulumLangthChange();
}

//--------------------------------------------------
// 内積が一定以内かつ最も近いオブジェクトのポインタを返す（選択）
//--------------------------------------------------
void PemdulumManager::PemgulumSelect() {
	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
	nextPemdulumVector_Langth_ = 9999.f;
	// スティックの入力があるとき
	if (IMGLA.x != 0 && IMGLA.y != 0) {
		for (auto& pemdulum : pemgulumList_) {
			if (pSelectedPemdulum != pemdulum) {
				DirectX::SimpleMath::Vector3 PP = pemdulum->GetComponent<TransformComponent>()->GetPosition();			// PemdulumPosition
				DirectX::SimpleMath::Vector3 SPP = pSelectedPemdulum->GetComponent<TransformComponent>()->GetPosition();	// SelectedPemdulumPosition
				// ベクトルの正規化
				stickVector_Langth_ = std::sqrt(IMGLA.x * IMGLA.x + IMGLA.y * IMGLA.y);
				stickVector_Normalize_ = { IMGLA.x / stickVector_Langth_, IMGLA.y / stickVector_Langth_ };
				pemdulumVector_Langth_ = std::sqrt((PP.x - SPP.x) * (PP.x - SPP.x) + (PP.y - SPP.y) * (PP.y - SPP.y));
				pemdulumVector_Normalize_ = { (PP.x - SPP.x) / pemdulumVector_Langth_,(PP.y - SPP.y) / pemdulumVector_Langth_ };
				// 内積の計算
				innerProduct_ = stickVector_Normalize_.x * pemdulumVector_Normalize_.x + stickVector_Normalize_.y * pemdulumVector_Normalize_.y;

				if (innerProduct_ > InnerProductLimit && nextPemdulumVector_Langth_ > pemdulumVector_Langth_) {
					nextPemdulumVector_Langth_ = pemdulumVector_Langth_;
					pNextPemdulum = pemdulum;
				}
			}
		}
		pSelectedPemdulum = pNextPemdulum;
	}
}

//--------------------------------------------------
// 振り子の状態変異
//--------------------------------------------------
void PemdulumManager::PemdulumMovementChange() {
	// Aボタン（動作の変更）
	if (IM.GetButtonTrigger(XINPUT_A)) {
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
	if (IM.GetButtonTrigger(XINPUT_UP)) {
		if (langthState_ != LangthState::shortLangth) {
			langthState_ -= LangthChange;
		}
	}
	// 十字↓（長くする）
	if (IM.GetButtonTrigger(XINPUT_DOWN)) {
		if (langthState_ != LangthState::longLangth) {
			langthState_ += LangthChange;
		}
	}
}