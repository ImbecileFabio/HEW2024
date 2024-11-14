//==================================================
// [Component.cpp] コンポーネントのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：コンポーネントの大元の定義
//==================================================

/*----- インクルード -----*/
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

	// カメラ
	, "CameraComponent"

};

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Component::Component(std::shared_ptr<GameObject> _owner, int _updateOrder)
	: owner_(_owner)
	, update_order_(_updateOrder)
{
	owner_->AddComponent(this);
}

Component::~Component()
{
	GetOwner()->RemoveComponent(this);

}

//--------------------------------------------------
// コンポーネントの姿勢制御の更新
//--------------------------------------------------
void Component::OnUpdateWorldTransform()
{
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
