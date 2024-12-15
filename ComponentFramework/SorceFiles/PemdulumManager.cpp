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
	// �U��q�̌����A�m��
	for (GameObject* object : GameManager::GetGameObjects()) {
		if (object->GetType() == "Pendulum")
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
	// if(�X�e�B�b�N�̓���){
	//	pSelectedPemdulum = ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ��֐�
	// }
	PemdulumMovementChange();
	PemgulumLangthChange();
}

//--------------------------------------------------
// ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ��i�I���j
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
// �U��q�̏�ԕψ�
//--------------------------------------------------
void PemdulumManager::PemdulumMovementChange() {
	// A�{�^���i����̕ύX�j
	if (InputManager::GetButtonTrigger(XINPUT_A)) {
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
	if (InputManager::GetButtonTrigger(XINPUT_UP)) {
		if (langthState_ != LangthState::shortLangth) {
			langthState_ -= LangthChange;
		} else {
			// ���������Ȃ�
		}
	}
	// �\�����i��������j
	if (InputManager::GetButtonTrigger(XINPUT_DOWN)) {
		if (langthState_ != LangthState::longLangth) {
			langthState_ += LangthChange;
		} else {
			// ���������Ȃ�
		}
	}
}