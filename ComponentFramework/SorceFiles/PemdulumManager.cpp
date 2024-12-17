//==================================================
// [PemdulumManager.cpp] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̊Ǘ��i�I���j
//==================================================

#include "PemdulumManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Component/PendulumMovementComponent.h"

//#define ControllerPlay

PemdulumManager* PemdulumManager::instance_ = nullptr;

//--------------------------------------------------
// �R���X�g���N�^�E�f�X�g���N�^
//--------------------------------------------------
PemdulumManager::PemdulumManager(){
	Init();
}
PemdulumManager::~PemdulumManager(){
	Uninit();
}

//--------------------------------------------------
// �����������E�I�������E�X�V����
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
// �I�u�W�F�N�g��ǉ�
//-----------------------------------------------------------------
void PemdulumManager::AddGameObject(GameObject* _gameObject)
{
	pemgulumList_.push_back(_gameObject);
}
//-----------------------------------------------------------------
// �I�u�W�F�N�g���폜
//-----------------------------------------------------------------
void PemdulumManager::RemoveGameObject(GameObject* _gameObject)
{
	pemgulumList_.remove(_gameObject);

}

//--------------------------------------------------
// ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ��i�I���j
//--------------------------------------------------
void PemdulumManager::PemgulumSelect() {
#ifdef ControllerPlay
	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
	nextPemdulumVector_Langth_ = 9999.f;
	// �X�e�B�b�N�̓��͂�����Ƃ�
	if (IMGLA.x != 0 && IMGLA.y != 0) {
		for (auto& pemdulum : pemgulumList_) {
			if (pSelectedPemdulum != pemdulum) {
				DirectX::SimpleMath::Vector3 PP = pemdulum->GetComponent<TransformComponent>()->GetPosition();			// PemdulumPosition
				DirectX::SimpleMath::Vector3 SPP = pSelectedPemdulum->GetComponent<TransformComponent>()->GetPosition();	// SelectedPemdulumPosition
				// �x�N�g���̐��K��
				stickVector_Langth_ = std::sqrt(IMGLA.x * IMGLA.x + IMGLA.y * IMGLA.y);
				stickVector_Normalize_ = { IMGLA.x / stickVector_Langth_, IMGLA.y / stickVector_Langth_ };
				pemdulumVector_Langth_ = std::sqrt((PP.x - SPP.x) * (PP.x - SPP.x) + (PP.y - SPP.y) * (PP.y - SPP.y));
				pemdulumVector_Normalize_ = { (PP.x - SPP.x) / pemdulumVector_Langth_,(PP.y - SPP.y) / pemdulumVector_Langth_ };
				// ���ς̌v�Z
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
// �U��q�̏�ԕψ�
//--------------------------------------------------
void PemdulumManager::PemdulumMovementChange() {
PendulumMovementComponent* SPM = pSelectedPemdulum->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// A�{�^���i����̕ύX�j
	if (IM.GetButtonTrigger(XINPUT_A)) {
		PM->SetPemdulumMovement(!PM->GetPemdulumMovement());
	}
#else
	// A�{�^���i����̕ύX�j
	if (IM.GetKeyTrigger(VK_M)) {
		SPM->SetPemdulumMovement(!SPM->GetPemdulumMovement());
	}
#endif
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
void PemdulumManager::PemgulumLangthChange() {
PendulumMovementComponent* SPM = pSelectedPemdulum->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// �\�����i�Z������j
	if (IM.GetButtonTrigger(XINPUT_UP)) {
		if (langthState_ != LangthState::shortLangth) {
			langthState_ -= LangthChange;
		}
	}
	// �\�����i��������j
	if (IM.GetButtonTrigger(XINPUT_DOWN)) {
		if (langthState_ != LangthState::longLangth) {
			langthState_ += LangthChange;
		}
	}
#else
	// �\�����i�Z������j
	if (IM.GetKeyTrigger(VK_I)) {
		if (SPM->GetLangthState() != LangthState::shortLangth) {
			SPM->SetLangthState(static_cast<LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
		}
	}
	// �\�����i��������j
	if (IM.GetKeyTrigger(VK_K)) {
		if (SPM->GetLangthState() != LangthState::longLangth) {
			SPM->SetLangthState(static_cast<LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
		}
	}
#endif
}

//--------------------------------------------------
// �C���X�^���X�̐���
//--------------------------------------------------
void PemdulumManager::SetSelectedPemdulum(GameObject* _pSelectedPemdulum) {
	pSelectedPemdulum = _pSelectedPemdulum;
	pSelectedPemdulum->GetComponent<PendulumMovementComponent>()->SetPemdulumSelected(true);
}