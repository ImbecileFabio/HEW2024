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
#include "GameObjects/GameObject/HammerCursor.h"
#include "GameObjects/Component/PendulumMovementComponent.h"
#include <algorithm>
//#define ControllerPlay

PendulumManager* PendulumManager::instance_ = nullptr;
bool PendulumManager::ComparePendulum(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
{
	if (a.y != b.y) {
		return a.y > b.y; // Y座標が小さい順
	}
	return a.x < b.x; // X座標が小さい順（Yが同じなら）
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
// 初期化処理・終了処理・更新処理
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
		if (!is_sort_)
		{
			SortPendulums(pendulum_list_); // ここでソート
			is_sort_ = true;
		}
		PendulumSelect();
		PendulumMovementChange();
		PendulumLangthChange();
		PendulumDirectionChange();
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
	auto iter = std::find(pendulum_list_.begin(), pendulum_list_.end(), _gameObject);
	// 稼働コンテナ
	iter = std::find(pendulum_list_.begin(), pendulum_list_.end(), _gameObject);
	if (iter != pendulum_list_.end())
	{
		std::iter_swap(iter, pendulum_list_.end() - 1);	// コンテナの最後尾と入れ替え
		pendulum_list_.pop_back();						// 稼働コンテナから削除
	}
}

//--------------------------------------------------
// 内積が一定以内かつ最も近いオブジェクトのポインタを返す（選択）
//--------------------------------------------------
void PendulumManager::PendulumSelect() {
//#ifdef ControllerPlay
//	maxIndex_ = pendulum_list_.size() - 1;	// 添え字の調整
//
//	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
//	nextPendulumVector_Langth_ = 9999.f;
//	// スティックの入力があるとき
//	if (IMGLA.x != 0 && IMGLA.y != 0) 
//	{
//		if (IMGLA.x > 0)
//		{
//			selectIndex_++;
//		}
//		if (IMGLA.x < 0)
//		{
//			selectIndex_--;
//		}
//		if (maxIndex_ < selectIndex_)
//		{
//			selectIndex_ = 0;
//		}
//		if (-1 == selectIndex_)
//		{
//			selectIndex_ = maxIndex_;
//		}
//	}
//	pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
//	pHammerCursor_->SetIsUiDraw(true);
//	pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
//	pHammerCursor_->HammerCursorMove();
//#else
	maxIndex_ = pendulum_list_.size() - 1;	// 添え字の調整
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

//#endif
}

//--------------------------------------------------
// 振り子の状態変異
//--------------------------------------------------
void PendulumManager::PendulumMovementChange() {
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// Aボタン（動作の変更）
	if (IM.GetButtonTrigger(XINPUT_A)) {
		SPM->SetPendulumMovement(!SPM->GetPendulumMovement());
	}
#else
	//if (GM->GetIsHammerMax()) return;
	// Mキー（動作の変更）
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
// 長さの変更
//--------------------------------------------------
void PendulumManager::PendulumLangthChange() {
PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
#ifdef ControllerPlay
	// 十字↑（短くする）
	if (IM.GetButtonTrigger(XINPUT_UP)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::shortLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
			GM->HammerCountDown();
		}
	}
	// 十字↓（長くする）
	if (IM.GetButtonTrigger(XINPUT_DOWN)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::longLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
			GM->HammerCountDown();
		}
	}
#else
	//if (GM->GetIsHammerMax()) return;	
	// Iキー（短くする）
	if (IM.GetKeyTrigger(VK_I)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::shortLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
			GM->HammerCountDown();
		}
	}
	// Kキー（長くする）
	if (IM.GetKeyTrigger(VK_K)) {
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::longLangth) {
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) + 1));
			GM->HammerCountDown();
		}
	}
#endif
}

//--------------------------------------------------
// 振り子を叩く向きの変更
//--------------------------------------------------
void PendulumManager::PendulumDirectionChange() {
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	pHammerCursor_->SetDirection(SPM->GetPendulumDirection());

#ifdef ControllerPlay
	// 十字左（左向き）
	if (IM.GetButtonTrigger(XINPUT_LEFT)) {
		if (SPM->GetPendulumDirection() != -1) {
			SPM->SetPendulumDirection(-1);
			pHammerCursor_->SetDirection(-1);
		}
	}
	// 十字右（右向き）
	else if (IM.GetButtonTrigger(XINPUT_RIGHT)) {
		SPM->SetPendulumDirection(1);
		pHammerCursor_->SetDirection(1);
	}
#else
	// Nキー（向きの変更）
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
// インスタンスの生成
//--------------------------------------------------
void PendulumManager::SetSelectedPendulum(GameObject* _pSelectedPemdulum) {
	pendulum_list_[0]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
}