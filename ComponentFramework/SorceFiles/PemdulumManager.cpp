//==================================================
// [PemdulumManager.cpp] 
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の管理（選択）
//==================================================

#include "PemdulumManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Component/PendulumMovementComponent.h"

//#define ControllerPlay

PemdulumManager* PemdulumManager::instance_ = nullptr;

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
}
void PemdulumManager::Uninit() {
	pemgulumList_.clear();
	pSelectedPemdulum = nullptr;
	DestroyInstance();
}
void PemdulumManager::Update(){
	if (pSelectedPemdulum != nullptr) {
		PemgulumSelect();
		PemdulumMovementChange();
		PemgulumLangthChange();
	}
}

//-----------------------------------------------------------------
// オブジェクトを追加
//-----------------------------------------------------------------
void PemdulumManager::AddGameObject(GameObject* _gameObject)
{
	pemgulumList_.push_back(_gameObject);
}
//-----------------------------------------------------------------
// オブジェクトを削除
//-----------------------------------------------------------------
void PemdulumManager::RemoveGameObject(GameObject* _gameObject)
{
	pemgulumList_.remove(_gameObject);

}

//--------------------------------------------------
// 内積が一定以内かつ最も近いオブジェクトのポインタを返す（選択）
//--------------------------------------------------
void PemdulumManager::PemgulumSelect() {
#ifdef ControllerPlay
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
		pSelectedPemdulum->GetComponent<PendulumMovementComponent>()->SetPemdulumSelected(true);
	}
#else
	pNextPemdulum = nullptr;
	if (IM.GetKeyTrigger(VK_L)) {
		for (auto& pemdulum : pemgulumList_) {
			if (pSelectedPemdulum != pemdulum &&
				pSelectedPemdulum->GetComponent<TransformComponent>()->GetPosition().x <
				pemdulum->GetComponent<TransformComponent>()->GetPosition().x) {
				if (pNextPemdulum == nullptr) {
					pNextPemdulum = pemdulum;
				}
				else if (pNextPemdulum->GetComponent<TransformComponent>()->GetPosition().x >
					pemdulum->GetComponent<TransformComponent>()->GetPosition().x) {
					pNextPemdulum = pemdulum;
				}
			}
		}
	}
	if (IM.GetKeyTrigger(VK_J)) {
		for (auto& pemdulum : pemgulumList_) {
			if (pSelectedPemdulum != pemdulum &&
				pSelectedPemdulum->GetComponent<TransformComponent>()->GetPosition().x >
				pemdulum->GetComponent<TransformComponent>()->GetPosition().x) {
				if (pNextPemdulum == nullptr) {
					pNextPemdulum = pemdulum;
				}
				else if (pNextPemdulum->GetComponent<TransformComponent>()->GetPosition().x <
					pemdulum->GetComponent<TransformComponent>()->GetPosition().x) {
					pNextPemdulum = pemdulum;
				}
			}
		}
	}
	if (pNextPemdulum != nullptr) {
		pSelectedPemdulum = pNextPemdulum;
		pSelectedPemdulum->GetComponent<PendulumMovementComponent>()->SetPemdulumSelected(true);
	}
#endif
}

//--------------------------------------------------
// 振り子の状態変異
//--------------------------------------------------
void PemdulumManager::PemdulumMovementChange() {
PendulumMovementComponent* SPM = pSelectedPemdulum->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// Aボタン（動作の変更）
	if (IM.GetButtonTrigger(XINPUT_A)) {
		PM->SetPemdulumMovement(!PM->GetPemdulumMovement());
	}
#else
	// Aボタン（動作の変更）
	if (IM.GetKeyTrigger(VK_A)) {
		SPM->SetPemdulumMovement(!SPM->GetPemdulumMovement());
	}
#endif
}

//--------------------------------------------------
// 長さの変更
//--------------------------------------------------
void PemdulumManager::PemgulumLangthChange() {
PendulumMovementComponent* SPM = pSelectedPemdulum->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
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
#else
	// 十字↑（短くする）
	if (IM.GetKeyTrigger(VK_I)) {
		if (SPM->GetLangthState() != LangthState::shortLangth) {
			SPM->SetLangthState(static_cast<LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
		}
	}
	// 十字↓（長くする）
	if (IM.GetKeyTrigger(VK_K)) {
		if (SPM->GetLangthState() != LangthState::longLangth) {
			SPM->SetLangthState(static_cast<LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
		}
	}
#endif
}

//--------------------------------------------------
// インスタンスの生成
//--------------------------------------------------
void PemdulumManager::SetSelectedPemdulum(GameObject* _pSelectedPemdulum) {
	pSelectedPemdulum = _pSelectedPemdulum;
	pSelectedPemdulum->GetComponent<PendulumMovementComponent>()->SetPemdulumSelected(true);
}