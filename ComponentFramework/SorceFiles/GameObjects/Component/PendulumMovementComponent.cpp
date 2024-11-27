//==================================================
// [PendulumMovementComponent.cpp] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//==================================================

#include "PendulumMovementComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
PendulumMovementComponent::PendulumMovementComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder) {
	std::cout << std::format("＜PendulumMovementComponent＞ -> Constructor\n");

	Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
PendulumMovementComponent::~PendulumMovementComponent() {
	std::cout << std::format("＜PendulumMovementComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void PendulumMovementComponent::Init() {

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void PendulumMovementComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void PendulumMovementComponent::Updata() {

}