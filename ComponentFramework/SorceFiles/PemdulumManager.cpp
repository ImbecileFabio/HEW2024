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
#include <algorithm>
//#define ControllerPlay

PendulumManager* PendulumManager::instance_ = nullptr;
void PendulumManager::PendulumSearch()
{
	if (pendulum_list_.size() == 0) return;
	pendulum_list_[0]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
	pHammerCursor_->SetIsUiDraw(true);
	pHammerCursor_->SetOriginPos(pendulum_list_[0]->GetTransformComponent()->GetPosition());
	pHammerCursor_->HammerCursorMove();
}
bool PendulumManager::ComparePendulum(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
{
	if (a.y != b.y) {
		return a.y > b.y; // Y���W����������
	}
	return a.x < b.x; // X���W�����������iY�������Ȃ�j
}
void PendulumManager::SortPendulums(std::vector<GameObject*>& pendulum_list_)
{
	std::sort(pendulum_list_.begin(), pendulum_list_.end(),
		[](GameObject* a, GameObject* b) {
			return ComparePendulum(a->GetTransformComponent()->GetPosition(),
				b->GetTransformComponent()->GetPosition());
		});
}
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
void PendulumManager::Uninit()
{
	pendulum_list_.clear();
	pSelectedPendulum = nullptr;
}
void PendulumManager::Update()
{
	if (!pHammerCursor_) return;
	if (pendulum_list_.size() > 0)
	{
		if (!is_sort_)
		{
			SortPendulums(pendulum_list_); // �����Ń\�[�g
			is_sort_ = true;
		}
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
void PendulumManager::PendulumSelect() 
{
	maxIndex_ = static_cast<int>(pendulum_list_.size()) - 1;	// �Y�����̒���

	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
	nextPendulumVector_Langth_ = 9999.f;
	bool indexChanged = false; // �C���f�b�N�X���ύX���ꂽ��

	float threshold = 0.5f; // ���͌��o�̂������l
	float yLimit = 0.3f;    // �����͂Ɣ��肷�邽�߂� Y ���̋��e�͈�
	// �X�e�B�b�N�̓��͂�����Ƃ�
	if (std::abs(IMGLA.x) > threshold && std::abs(IMGLA.y) < yLimit)
	{
		if (prevIMGLA_.x <= threshold && IMGLA.x > threshold)
		{
			selectIndex_++;
			indexChanged = true;
		}
		else if (prevIMGLA_.x >= -threshold && IMGLA.x < -threshold)
		{
			selectIndex_--;
			indexChanged = true;
		}
	}
	prevIMGLA_ = IMGLA;

	if (IM.GetKeyTrigger(VK_RIGHT))
	{
		selectIndex_++;
		indexChanged = true;
	}
	if (IM.GetKeyTrigger(VK_LEFT))
	{
		selectIndex_--;
		indexChanged = true;
	}
	// **���ʏ����F�͈͒���**
	if (indexChanged)
	{
		if (selectIndex_ >= maxIndex_)
		{
			selectIndex_ = 0;
		}
		if (selectIndex_ < 0)
		{
			selectIndex_ = maxIndex_;
		}

		// **�I�������U��q�̏���**
		pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
		pHammerCursor_->SetIsUiDraw(true);
		pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
		pHammerCursor_->HammerCursorMove();
	}
}

//--------------------------------------------------
// �U��q�̏�ԕψ�
//--------------------------------------------------
void PendulumManager::PendulumMovementChange() {
	//if (GM->GetIsHammerMax()) return;
	if (pendulum_list_.size() <= selectIndex_) return;
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	// M�L�[�i����̕ύX�j
	if (IM.GetKeyTrigger(VK_RETURN) || IM.GetButtonTrigger(XINPUT_A))
	{
		bool isPendulumMove = SPM->GetPendulumMovement();
		SPM->SetPendulumMovement(!isPendulumMove);
		if (!isPendulumMove)
		{
			GM->HammerCountDown();
		}
	}
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
void PendulumManager::PendulumLangthChange() 
{
	//if (GM->GetIsHammerMax()) return;	
	if (pendulum_list_.size() <= selectIndex_) return;
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	// I�L�[�i�Z������j
	if (IM.GetKeyTrigger(VK_UP) || IM.GetButtonTrigger(XINPUT_UP))
	{
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::shortLangth)
		{
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
			GM->HammerCountDown();
		}
	}
	// K�L�[�i��������j
	if (IM.GetKeyTrigger(VK_DOWN) || IM.GetButtonTrigger(XINPUT_DOWN))
	{
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::longLangth) 
		{
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
			GM->HammerCountDown();
		}
	}
}

//--------------------------------------------------
// �U��q��@�������̕ύX
//--------------------------------------------------
void PendulumManager::PendulumDirectionChange()
{
	//PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();

	//int newDirection = SPM->GetPendulumDirection(); // ���݂̌���

	//// �\���L�[���i�������j
	//if (IM.GetButtonTrigger(XINPUT_LEFT)) {
	//	newDirection = -1;
	//}
	//// �\���L�[�E�i�E�����j
	//else if (IM.GetButtonTrigger(XINPUT_RIGHT)) {
	//	newDirection = 1;
	//}
	//// N�L�[�i�����̕ύX�j
	//else if (IM.GetKeyTrigger(VK_N)) {
	//	newDirection = (newDirection == 1) ? -1 : 1; // ���]
	//}

	//// �������ς�����ꍇ�̂ݍX�V
	//if (newDirection != SPM->GetPendulumDirection()) {
	//	SPM->SetPendulumDirection(newDirection);
	//	pHammerCursor_->SetDirection(newDirection);
	//}

	//// �J�[�\���̈ʒu�X�V
	//pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
	//pHammerCursor_->HammerCursorMove();
	if (pendulum_list_.size() <= selectIndex_) return;
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	pHammerCursor_->SetDirection(SPM->GetPendulumDirection());

	// �\�����i�������j
	if (IM.GetButtonTrigger(XINPUT_LEFT)) {
		if (SPM->GetPendulumDirection() != -1) 
		{
			SPM->SetPendulumDirection(-1);
			pHammerCursor_->SetDirection(-1);
		}
	}
	// �\���E�i�E�����j
	else if (IM.GetButtonTrigger(XINPUT_RIGHT)) 
	{
		SPM->SetPendulumDirection(1);
		pHammerCursor_->SetDirection(1);
	}
	// N�L�[�i�����̕ύX�j
	if (IM.GetKeyTrigger(VK_N)) 
	{
		if (SPM->GetPendulumDirection() != -1)
		{
			SPM->SetPendulumDirection(-1);
			pHammerCursor_->SetDirection(-1);
		}
		else {
			SPM->SetPendulumDirection(1);
			pHammerCursor_->SetDirection(1);
		}
	}
	pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
	pHammerCursor_->HammerCursorMove();
}

//--------------------------------------------------
// �C���X�^���X�̐���
//--------------------------------------------------
void PendulumManager::SetSelectedPendulum(GameObject* _pSelectedPemdulum) {
	pendulum_list_[0]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
}