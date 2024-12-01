//==================================================
// [GameObject.cpp] ゲームオブジェクトのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームオブジェクトの大元の定義
//==================================================

/*----- インクルード -----*/
#include "GameObject.h"
#include "../GameManager.h"


// ゲームオブジェクトのリスト
const char* GameObject::GameObjectTypeNames[static_cast<int>(TypeID::MAX)] =
{
	// 自分自身
	"GameObject"

	// アクター（独立した役割を持つゲームオブジェクト）
	, "Player"
	, "Camera"
	, "Pendulum"
	, "Tile"
};

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
GameObject::GameObject(GameManager* _gameManager)
	: game_manager_(_gameManager)
	, state_(State::Active)
	, re_compute_transform_(true)
{
	game_manager_->AddGameObject(this);

	// 姿勢制御コンポーネントの追加
	transform_component_ = new TransformComponent(this);

	// ゲームオブジェクトの初期化
	this->Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
GameObject::~GameObject(void)
{
	// ゲームオブジェクトの終了処理
	this->Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void GameObject::Init(void)
{
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void GameObject::Uninit(void)
{
	// コンポーネントの削除
	delete transform_component_;
}


//--------------------------------------------------
//	更新処理
//--------------------------------------------------
void GameObject::Update(void)
{
	if (state_ == State::Active)
	{
		if (re_compute_transform_)
		{
			ComputeWorldTransform();
		}
		UpdateComponents();		// コンポーネントの更新
		UpdateGameObject();		// オブジェクトの更新
	}
}

//--------------------------------------------------
// コンポーネントの更新処理
//--------------------------------------------------
void GameObject::UpdateComponents(void)
{
	for (auto& com : components_)
	{
		com->Update();
	}
}

//--------------------------------------------------
// 姿勢制御の更新
//--------------------------------------------------
void GameObject::ComputeWorldTransform()
{
	re_compute_transform_ = false;

	// 拡大, 回転, 平行移動の情報を格納
	for (auto& com : components_)
		com->OnUpdateWorldTransform();
}

//--------------------------------------------------
// コンポーネントの追加
//--------------------------------------------------
void GameObject::AddComponent(Component* _component)
{
	int my_update_order = _component->GetUpdateOrder();

	// 現在から追加されるコンポーネントのUpdateOrderと
	// 各コンポーネントのUpdateOrderとを比較
	// UpdateOrderが昇順になるように適時追加してく
	auto iter = components_.begin();
	for (; iter != components_.end(); ++iter)
	{
		if (my_update_order < (*iter)->GetUpdateOrder()) { break; }
	}
	components_.insert(iter, _component);
}

//--------------------------------------------------
// コンポーネントの削除
//--------------------------------------------------
void GameObject::RemoveComponent(Component* _component)
{
	auto iter = std::find(components_.begin()
		, components_.end()
		, _component);	// 探す対象

	if (iter != components_.end())
	{
		components_.erase(iter);	// 削除
	}
}