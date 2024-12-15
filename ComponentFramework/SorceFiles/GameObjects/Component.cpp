//==================================================
// [Component.cpp] コンポーネントのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：コンポーネントの大元の定義
//==================================================

/*----- インクルード -----*/
#include <cassert>

#include "Component.h"
#include "GameObject.h"

// コンポーネントのリスト
const char* Component::ComponentTypeNames[static_cast<int>(TypeID::MAX)] =
{
	// 自分自身
	"Component"

	//ここに追加したコンポーネントを追加していく
	// レンダリング
	, "RenderComponent"
	, "SpriteComponent"
	
	// 姿勢制御
	, "TransformComponent"
	// リジッドボディ
	, "RigidBodyComponent"
	, "VelocityComponent"
	// コライダー
	, "ColliderBaseComponent"
	, "BoxColliderComponent"
	, "CircleColliderComponent"
	// イベント
	, "EventBaseComponent"
	, "ColliderEventComponent"

	// ロボット
	, "RobotMoveComponent"
	// タイムゾーン
	, "TimeZoneComponent"
	// 振り子
	, "PendulumMovementComponent"
	// リフト
	, "LiftComponent"
	// カメラ
	, "CameraComponent"
};

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Component::Component(GameObject* _owner, int _updateOrder)
	: owner_(_owner)				// 所有者
	, update_order_(_updateOrder)	// 更新順
{
	// updateOrderは0以上、100以下で設定
	if (update_order_ < 0 || update_order_ > 100) { 
		std::cout << std::format("[Component]-> UpdateOrder が範囲外で指定されました\n");
		update_order_ = 0; 
	}
	owner_->AddComponent(this);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Component::~Component()
{
	owner_->RemoveComponent(this);
}


//--------------------------------------------------
// コンポーネントの状態の読み込み
//--------------------------------------------------
void Component::LoadProperties(void)
{
}

//--------------------------------------------------
// コンポーネントの状態の保存
//--------------------------------------------------
void Component::SaveProperties(void)
{
}
