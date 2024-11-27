//==================================================
// [AngularVelocityComponent.cpp] 角速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//		４．角速度、回転
//==================================================

#include "AngularVelocityComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
AngularVelocityComponent::AngularVelocityComponent(GameObject* _owner, int _updateOrder)
	:RigidbodyComponent(_owner, _updateOrder) {
	std::cout << std::format("＜AngularVelocityComponent＞ -> Constructor\n");

	Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
AngularVelocityComponent::~AngularVelocityComponent() {
	std::cout << std::format("＜AngularVelocityComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void AngularVelocityComponent::Init() {

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void AngularVelocityComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void AngularVelocityComponent::Updata() {
	//UpdateVelocity();
}