//==================================================
// [PendulumManager.cpp] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̊Ǘ��i�I���j
//==================================================

#include "PemdulumManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/GameObject/HammerCursor.h"
#include "GameObjects/Component/PendulumMovementComponent.h"

//#define ControllerPlay

PendulumManager* PendulumManager::instance_ = nullptr;
//--------------------------------------------------
// @brief �U��q�̌���
//--------------------------------------------------
//void PendulumManager::PendulumSearch()
//{
//	pSelectedPendulum = nullptr;
//
//	for (auto& pemdulum : pendulum_list_)
//	{
//		if (pOldPendulum != pemdulum)
//		{
//			pSelectedPendulum = pemdulum;
//			pSelectedPendulum->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
//			break;
//		}
//	}
//
//	if (!pSelectedPendulum)
//	{
//		pHammerCursor_->SetOriginPos({ -10000.0f, 0.0f, 0.0f });
//		pHammerCursor_->SetIsUiDraw(false); // UI�̕`����I�t�ɂ���
//		pHammerCursor_->HammerCursorMove();
//		return;
//	}
//
//	pHammerCursor_->SetIsUiDraw(true); // UI�̕`����I���ɂ���
//	pHammerCursor_->SetOriginPos(pSelectedPendulum->GetTransformComponent()->GetPosition());
//	pHammerCursor_->HammerCursorMove();
//}
//--------------------------------------------------
// �R���X�g���N�^�E�f�X�g���N�^
//--------------------------------------------------
PendulumManager::PendulumManager(){
	Init();
}
PendulumManager::~PendulumManager(){
	Uninit();
}

//--------------------------------------------------
// �����������E�I�������E�X�V����
//--------------------------------------------------
void PendulumManager::Init(){
}
void PendulumManager::Uninit() {
	pendulum_list_.clear();
	pSelectedPendulum = nullptr;
}
void PendulumManager::Update()
{
	if (!pHammerCursor_) return;
	if (pendulum_list_.size() > 0)
	{
		PendulumSelect();
		PendulumMovementChange();
		PendulumLangthChange();
		PendulumDirectionChange();
	}
}

//-----------------------------------------------------------------
// �I�u�W�F�N�g��ǉ�
//-----------------------------------------------------------------
void PendulumManager::AddGameObject(GameObject* _gameObject)
{
	pendulum_list_.push_back(_gameObject);
}
//-----------------------------------------------------------------
// �I�u�W�F�N�g���폜
//-----------------------------------------------------------------
void PendulumManager::RemoveGameObject(GameObject* _gameObject)
{
	auto iter = std::find(pendulum_list_.begin(), pendulum_list_.end(), _gameObject);
	// �ғ��R���e�i
	iter = std::find(pendulum_list_.begin(), pendulum_list_.end(), _gameObject);
	if (iter != pendulum_list_.end())
	{
		std::iter_swap(iter, pendulum_list_.end() - 1);	// �R���e�i�̍Ō���Ɠ���ւ�
		pendulum_list_.pop_back();						// �ғ��R���e�i����폜
	}
}

//--------------------------------------------------
// ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ��i�I���j
//--------------------------------------------------
void PendulumManager::PendulumSelect() {
#ifdef ControllerPlay
	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
	nextPendulumVector_Langth_ = 9999.f;
	// �X�e�B�b�N�̓��͂�����Ƃ�
	if (IMGLA.x != 0 && IMGLA.y != 0) {
		for (auto& pemdulum : pendulum_list_) {
			if (pSelectedPendulum != pemdulum) {
				DirectX::SimpleMath::Vector3 PP = pemdulum->GetTransformComponent()->GetPosition();			// PemdulumPosition
				DirectX::SimpleMath::Vector3 SPP = pSelectedPendulum->GetTransformComponent()->GetPosition();	// SelectedPemdulumPosition
				// �x�N�g���̐��K��
				stickVector_Langth_ = std::sqrt(IMGLA.x * IMGLA.x + IMGLA.y * IMGLA.y);
				stickVector_Normalize_ = { IMGLA.x / stickVector_Langth_, IMGLA.y / stickVector_Langth_ };
				pendulumVector_Langth_ = std::sqrt((PP.x - SPP.x) * (PP.x - SPP.x) + (PP.y - SPP.y) * (PP.y - SPP.y));
				pendulumVector_Normalize_ = { (PP.x - SPP.x) / pendulumVector_Langth_,(PP.y - SPP.y) / pendulumVector_Langth_ };
				// ���ς̌v�Z
				innerProduct_ = stickVector_Normalize_.x * pendulumVector_Normalize_.x + stickVector_Normalize_.y * pendulumVector_Normalize_.y;

				if (innerProduct_ > InnerProductLimit && nextPendulumVector_Langth_ > pendulumVector_Langth_) {
					nextPendulumVector_Langth_ = pendulumVector_Langth_;
					pNextPendulum = pemdulum;
				}
			}
		}
	}

	if (pNextPendulum)
	{
		pOldPendulum = pSelectedPendulum; // pSelectedPendulum ��ۑ�
		pSelectedPendulum = pNextPendulum;
		pSelectedPendulum->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
	}

	if (pSelectedPendulum)
	{
		pHammerCursor_->SetIsUiDraw(true);
		pHammerCursor_->SetOriginPos(pSelectedPendulum->GetTransformComponent()->GetPosition());
		pHammerCursor_->HammerCursorMove();
	}
#else
	maxIndex_ = pendulum_list_.size() - 1;	// �Y�����̒���
	if (IM.GetKeyTrigger(VK_L))
	{
		selectIndex_++;
	}
	if (IM.GetKeyTrigger(VK_J))
	{
		selectIndex_--;
	}
	if (maxIndex_ < selectIndex_)
	{
		selectIndex_ = 0;
	}
	if (-1 == selectIndex_)
	{
		selectIndex_ = maxIndex_;
	}
	pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
	pHammerCursor_->SetIsUiDraw(true);
	pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
	pHammerCursor_->HammerCursorMove();

#endif
}

//--------------------------------------------------
// �U��q�̏�ԕψ�
//--------------------------------------------------
void PendulumManager::PendulumMovementChange() {
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// A�{�^���i����̕ύX�j
	if (IM.GetButtonTrigger(XINPUT_A)) {
		SPM->SetPendulumMovement(!SPM->GetPendulumMovement());
	}
#else
	//if (GM->GetIsHammerMax()) return;
	// M�L�[�i����̕ύX�j
	if (IM.GetKeyTrigger(VK_M))
	{
		bool isPendulumMove = SPM->GetPendulumMovement();
		SPM->SetPendulumMovement(!isPendulumMove);
		if (!isPendulumMove)
		{
			GM->HammerCountDown();
		}
	}
#endif
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
void PendulumManager::PendulumLangthChange() {
PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// �\�����i�Z������j
	if (IM.GetButtonTrigger(XINPUT_UP)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::shortLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
			GM->HammerCountDown();
		}
	}
	// �\�����i��������j
	if (IM.GetButtonTrigger(XINPUT_DOWN)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::longLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
			GM->HammerCountDown();
		}
	}
#else
	//if (GM->GetIsHammerMax()) return;	
	// I�L�[�i�Z������j
	if (IM.GetKeyTrigger(VK_I)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::shortLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
			GM->HammerCountDown();
		}
	}
	// K�L�[�i��������j
	if (IM.GetKeyTrigger(VK_K)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::longLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
			GM->HammerCountDown();
		}
	}
#endif
}

//--------------------------------------------------
// �U��q��@�������̕ύX
//--------------------------------------------------
void PendulumManager::PendulumDirectionChange() {
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	pHammerCursor_->SetDirection(SPM->GetPendulumDirection());

#ifdef ControllerPlay
	// �\�����i�������j
	if (IM.GetButtonTrigger(XINPUT_LEFT)) {
		if (SPM->GetPendulumDirection() != -1) {
			SPM->SetPendulumDirection(-1);
			pHammerCursor_->SetDirection(-1);
		}
	}
	// �\���E�i�E�����j
	else if (IM.GetButtonTrigger(XINPUT_RIGHT)) {
		SPM->SetPendulumDirection(1);
		pHammerCursor_->SetDirection(1);
	}
#else
	// N�L�[�i�����̕ύX�j
	if (IM.GetKeyTrigger(VK_N)) {
		if (SPM->GetPendulumDirection() != -1) {
			SPM->SetPendulumDirection(-1);
			pHammerCursor_->SetDirection(-1);
		}
		else {
			SPM->SetPendulumDirection(1);
			pHammerCursor_->SetDirection(1);
		}
	}
#endif
	pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
	pHammerCursor_->HammerCursorMove();
}

//--------------------------------------------------
// �C���X�^���X�̐���
//--------------------------------------------------
void PendulumManager::SetSelectedPendulum(GameObject* _pSelectedPemdulum) {
	pendulum_list_[0]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
}