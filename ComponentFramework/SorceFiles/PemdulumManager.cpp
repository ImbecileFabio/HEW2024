//==================================================
// [PemdulumManager.cpp] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̊Ǘ��i�I���j
//==================================================

#include "PemdulumManager.h"
#include "GameManager.h"
#include "GameObjects/GameObject.h"
#include "InputManager.h"

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
	GM = new GameManager;
	// �U��q�̌����A�m��
	for (GameObject* object : GM->GetGameObjects()) {
		if (object->GetType() == GameObject::TypeID::Pendulum)
		pemgulumList_.push_back(object);
	}
	pSelectedPemdulum = pemgulumList_.front();

	// �U��q�̓���A�����̏��
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
// ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ��i�I���j
//--------------------------------------------------
void PemdulumManager::PemgulumSelect() {
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
	}
}

//--------------------------------------------------
// �U��q�̏�ԕψ�
//--------------------------------------------------
void PemdulumManager::PemdulumMovementChange() {
	// A�{�^���i����̕ύX�j
	if (IM.GetButtonTrigger(XINPUT_A)) {
		if (pemdulumMovement_) {
			pemdulumMovement_ = !pemdulumMovement_;
		} else {
			pemdulumMovement_ = !pemdulumMovement_;
		}
	}
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
void PemdulumManager::PemgulumLangthChange() {
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
}