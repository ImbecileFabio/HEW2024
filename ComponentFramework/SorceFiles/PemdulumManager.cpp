//==================================================
// [PendulumManager.cpp] 
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

PendulumManager* PendulumManager::instance_ = nullptr;

//--------------------------------------------------
// コンストラクタ・デストラクタ
//--------------------------------------------------
PendulumManager::PendulumManager(){
	Init();
}
PendulumManager::~PendulumManager(){
	Uninit();
}

//--------------------------------------------------
// 初期化処理・終了処理・更新処理
//--------------------------------------------------
void PendulumManager::Init(){
}
void PendulumManager::Uninit() {
	pendulum_list_.clear();
	pSelectedPendulum = nullptr;
	DestroyInstance();
}
void PendulumManager::Update(){
	if (pSelectedPendulum != nullptr) {
		PendulumSelect();
		PendulumMovementChange();
		PendulumLangthChange();
	}
}

//-----------------------------------------------------------------
// オブジェクトを追加
//-----------------------------------------------------------------
void PendulumManager::AddGameObject(GameObject* _gameObject)
{
	pendulum_list_.push_back(_gameObject);
}
//-----------------------------------------------------------------
// オブジェクトを削除
//-----------------------------------------------------------------
void PendulumManager::RemoveGameObject(GameObject* _gameObject)
{
	pendulum_list_.remove(_gameObject);

}

//--------------------------------------------------
// 内積が一定以内かつ最も近いオブジェクトのポインタを返す（選択）
//--------------------------------------------------
void PendulumManager::PendulumSelect() {
#ifdef ControllerPlay
	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
	nextPendulumVector_Langth_ = 9999.f;
	// スティックの入力があるとき
	if (IMGLA.x != 0 && IMGLA.y != 0) {
		for (auto& pemdulum : pendulum_list_) {
			if (pSelectedPendulum != pemdulum) {
				DirectX::SimpleMath::Vector3 PP = pemdulum->GetTransformComponent()->GetPosition();			// PemdulumPosition
				DirectX::SimpleMath::Vector3 SPP = pSelectedPendulum->GetTransformComponent()->GetPosition();	// SelectedPemdulumPosition
				// ベクトルの正規化
				stickVector_Langth_ = std::sqrt(IMGLA.x * IMGLA.x + IMGLA.y * IMGLA.y);
				stickVector_Normalize_ = { IMGLA.x / stickVector_Langth_, IMGLA.y / stickVector_Langth_ };
				pendulumVector_Langth_ = std::sqrt((PP.x - SPP.x) * (PP.x - SPP.x) + (PP.y - SPP.y) * (PP.y - SPP.y));
				pendulumVector_Normalize_ = { (PP.x - SPP.x) / pendulumVector_Langth_,(PP.y - SPP.y) / pendulumVector_Langth_ };
				// 内積の計算
				innerProduct_ = stickVector_Normalize_.x * pendulumVector_Normalize_.x + stickVector_Normalize_.y * pendulumVector_Normalize_.y;

				if (innerProduct_ > InnerProductLimit && nextPendulumVector_Langth_ > pendulumVector_Langth_) {
					nextPendulumVector_Langth_ = pendulumVector_Langth_;
					pNextPendulum = pemdulum;
				}
			}
		}
		pSelectedPendulum = pNextPendulum;
		pSelectedPendulum->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
	}
#else
	pNextPendulum = nullptr;
	if (IM.GetKeyTrigger(VK_L)) {
		for (auto& pemdulum : pendulum_list_) {
			if (pSelectedPendulum != pemdulum &&
				pSelectedPendulum->GetTransformComponent()->GetPosition().x <
				pemdulum->GetTransformComponent()->GetPosition().x) {
				if (pNextPendulum == nullptr) {
					pNextPendulum = pemdulum;
				}
				else if (pNextPendulum->GetTransformComponent()->GetPosition().x >
					pemdulum->GetTransformComponent()->GetPosition().x) {
					pNextPendulum = pemdulum;
				}
			}
		}
	}
	if (IM.GetKeyTrigger(VK_J)) {
		for (auto& pemdulum : pendulum_list_) {
			if (pSelectedPendulum != pemdulum &&
				pSelectedPendulum->GetTransformComponent()->GetPosition().x >
				pemdulum->GetTransformComponent()->GetPosition().x) {
				if (pNextPendulum == nullptr) {
					pNextPendulum = pemdulum;
				}
				else if (pNextPendulum->GetTransformComponent()->GetPosition().x <
					pemdulum->GetTransformComponent()->GetPosition().x) {
					pNextPendulum = pemdulum;
				}
			}
		}
	}
	if (pNextPendulum != nullptr) {
		pSelectedPendulum = pNextPendulum;
		pSelectedPendulum->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
	}
#endif
}

//--------------------------------------------------
// 振り子の状態変異
//--------------------------------------------------
void PendulumManager::PendulumMovementChange() {
PendulumMovementComponent* SPM = pSelectedPendulum->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// Aボタン（動作の変更）
	if (IM.GetButtonTrigger(XINPUT_A)) {
		PM->SetPendulumMovement(!PM->GetPendulumMovement());
	}
#else
	// Aボタン（動作の変更）
	if (IM.GetKeyTrigger(VK_M)) {
		SPM->SetPendulumMovement(!SPM->GetPendulumMovement());
	}
#endif
}

//--------------------------------------------------
// 長さの変更
//--------------------------------------------------
void PendulumManager::PendulumLangthChange() {
PendulumMovementComponent* SPM = pSelectedPendulum->GetComponent<PendulumMovementComponent>();
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
void PendulumManager::SetSelectedPendulum(GameObject* _pSelectedPemdulum) {
	pSelectedPendulum = _pSelectedPemdulum;
	pSelectedPendulum->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
}