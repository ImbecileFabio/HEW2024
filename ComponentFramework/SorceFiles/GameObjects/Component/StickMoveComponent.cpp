//==================================================
// [StickMoveComponent.cpp] 振り子の棒の動きコンポーネント
// 著者：HOGE太郎
//--------------------------------------------------
// 説明：振り子の棒の動きコンポーネントの定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include "StickMoveComponent.h"
#include "../../TileMapManager.h"

#include "../GameObject.h"
#include "../GameObject/Pendulum.h"

#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"


//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
StickMoveComponent::StickMoveComponent(GameObject* _owner, Pendulum* _pendulum, int _updateOrder)
	:Component(_owner, _updateOrder)
	, owner_pendulum_(_pendulum)
	, length_state_(LengthState::Middle)
	, stick_length_{}
{
	std::cout << std::format("＜StickMoveComponent＞ -> Constructor\n");

	owner_transform_ = owner_->GetTransformComponent();
	pendulum_transform_ = owner_pendulum_->GetTransformComponent();
	this->Init();
}

//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
StickMoveComponent::~StickMoveComponent()
{
	std::cout << std::format("＜StickMoveComponent＞ -> Destructor\n");
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void StickMoveComponent::Init()
{

}

//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void StickMoveComponent::Uninit()
{
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void StickMoveComponent::Update()
{
	// 棒の長さの変更
	this->ChangeStickLength();

	// 支点の位置
	auto startPos = owner_pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
	// 終点を計算
	auto endPos = owner_pendulum_->GetTransformComponent()->GetPosition();
	// 棒の回転角度を計算
	float stickAngle = std::atan2(endPos.y - startPos.y,endPos.x - startPos.x) - DirectX::XM_PIDIV2;

	// 終点の計算
	Vector3 stickPos = {
		(startPos.x + endPos.x) / 2.0f,
		(startPos.y + endPos.y) / 2.0f,
		0.0f
	};

	// 振り子の位置を設定
	owner_transform_->SetPosition(stickPos);
	owner_transform_->SetRotation(stickAngle);
	owner_transform_->SetSize(TILE_SIZE_X, stick_length_);
}

void StickMoveComponent::ChangeStickLength()
{
	switch (length_state_)
	{
	case LengthState::Short:
		stick_length_ = normalLangth - langthChange;
		break;
	case LengthState::Middle:
		stick_length_ = normalLangth;
		break;
	case LengthState::Long:
		stick_length_ = normalLangth + langthChange;
		break;
	}
}


//--------------------------------------------------
// @param _sPos： 支点, _length： 棒の長さ, _angle： 棒の角度
// @brief 描画する中心位置を計算する
// @return Vector3: 計算された座標
//--------------------------------------------------
Vector3 StickMoveComponent::CalculateEndPoint(Vector3& _sPos, float _length, float _angle)
{
	return {
		_sPos.x + _length * std::cos(_angle),
		_sPos.y + _length * std::sin(_angle),
		_sPos.z
	};
}