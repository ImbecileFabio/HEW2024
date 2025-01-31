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
void PendulumManager::PendulumSelect() 
{
	maxIndex_ = static_cast<int>(pendulum_list_.size()) - 1;	// 添え字の調整

	DirectX::XMFLOAT2 IMGLA = IM.GetLeftAnalogStick();	// InputManager GetLeftAnalogstick
	nextPendulumVector_Langth_ = 9999.f;
	bool indexChanged = false; // インデックスが変更されたか

	float threshold = 0.5f; // 入力検出のしきい値
	float yLimit = 0.3f;    // 横入力と判定するための Y 軸の許容範囲
	// スティックの入力があるとき
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
	// **共通処理：範囲調整**
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

		// **選択した振り子の処理**
		pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
		pHammerCursor_->SetIsUiDraw(true);
		pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
		pHammerCursor_->HammerCursorMove();
	}
}

//--------------------------------------------------
// 振り子の状態変異
//--------------------------------------------------
void PendulumManager::PendulumMovementChange() {
	//if (GM->GetIsHammerMax()) return;
	if (pendulum_list_.size() <= selectIndex_) return;
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	// Mキー（動作の変更）
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
// 長さの変更
//--------------------------------------------------
void PendulumManager::PendulumLangthChange() 
{
	//if (GM->GetIsHammerMax()) return;	
	if (pendulum_list_.size() <= selectIndex_) return;
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	// Iキー（短くする）
	if (IM.GetKeyTrigger(VK_UP) || IM.GetButtonTrigger(XINPUT_UP))
	{
		if (SPM->GetLangthState() != PendulumMovementComponent::LangthState::shortLangth)
		{
			SPM->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(static_cast<int>(SPM->GetLangthState()) - 1));
			GM->HammerCountDown();
		}
	}
	// Kキー（長くする）
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
// 振り子を叩く向きの変更
//--------------------------------------------------
void PendulumManager::PendulumDirectionChange()
{
	//PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();

	//int newDirection = SPM->GetPendulumDirection(); // 現在の向き

	//// 十字キー左（左向き）
	//if (IM.GetButtonTrigger(XINPUT_LEFT)) {
	//	newDirection = -1;
	//}
	//// 十字キー右（右向き）
	//else if (IM.GetButtonTrigger(XINPUT_RIGHT)) {
	//	newDirection = 1;
	//}
	//// Nキー（向きの変更）
	//else if (IM.GetKeyTrigger(VK_N)) {
	//	newDirection = (newDirection == 1) ? -1 : 1; // 反転
	//}

	//// 向きが変わった場合のみ更新
	//if (newDirection != SPM->GetPendulumDirection()) {
	//	SPM->SetPendulumDirection(newDirection);
	//	pHammerCursor_->SetDirection(newDirection);
	//}

	//// カーソルの位置更新
	//pHammerCursor_->SetOriginPos(pendulum_list_[selectIndex_]->GetTransformComponent()->GetPosition());
	//pHammerCursor_->HammerCursorMove();
	if (pendulum_list_.size() <= selectIndex_) return;
	PendulumMovementComponent* SPM = pendulum_list_[selectIndex_]->GetComponent<PendulumMovementComponent>();
	pHammerCursor_->SetDirection(SPM->GetPendulumDirection());

	// 十字左（左向き）
	if (IM.GetButtonTrigger(XINPUT_LEFT)) {
		if (SPM->GetPendulumDirection() != -1) 
		{
			SPM->SetPendulumDirection(-1);
			pHammerCursor_->SetDirection(-1);
		}
	}
	// 十字右（右向き）
	else if (IM.GetButtonTrigger(XINPUT_RIGHT)) 
	{
		SPM->SetPendulumDirection(1);
		pHammerCursor_->SetDirection(1);
	}
	// Nキー（向きの変更）
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
// インスタンスの生成
//--------------------------------------------------
void PendulumManager::SetSelectedPendulum(GameObject* _pSelectedPemdulum) {
	pendulum_list_[0]->GetComponent<PendulumMovementComponent>()->SetPendulumSelected(true);
}