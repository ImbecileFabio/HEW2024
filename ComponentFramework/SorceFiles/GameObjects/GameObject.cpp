//==================================================
// [GameObject.cpp] ゲームオブジェクトのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームオブジェクトの大元の定義
//==================================================

/*----- インクルード -----*/
#include "GameObject.h"
#include "../GameManager.h"
#include "../AudioManager.h"
#include "Component/ColliderComponent/BoxColliderComponent.h"
// オブジェクトの加算されていくID
int GameObject::next_object_id_ = 0;
// ゲームオブジェクトのリスト
const char* GameObject::GameObjectTypeNames[static_cast<int>(TypeID::MAX)] =
{
	// 自分自身
	"GameObject"

	// ゲームオブジェクト
	, "Player"
	, "Camera"
	, "Pendulum"
	, "Tile"
	, "Robot"
};

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
GameObject::GameObject(GameManager* _gameManager, std::string _objectName, int _order)
	: game_manager_(_gameManager)	// 所有者
	, object_name_(_objectName)		// オブジェクト名
	, update_order_(_order)			// 更新順q
	, state_(State::Active)			// 状態
	, re_compute_transform_(true)	// 姿勢情報の再計算
{
	// ゲームオブジェクトの登録
	game_manager_->AddGameObject(this);
	
	// 全体のIDを加算
	next_object_id_++;
	
	// オブジェクトのIDを設定
	object_id_ = next_object_id_;
	
	// 姿勢制御コンポーネントの追加
	transform_component_ = new TransformComponent(this);

	// ゲームオブジェクトの初期化
	this->Init();

	for (auto ObjctList : game_manager_->GetGameObjects()) {
		if (this->GetType() == ObjctList->GetType()) {
			object_fier++;
		}
	}
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
	// コンポーネントの初期化
	this->InitComponent();
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void GameObject::Uninit(void)
{
	// コンポーネントの削除
	delete transform_component_;

	// 削除対象リストを作成
	std::vector<Component*> deadComponents;

	// コンポーネントを削除対象リストに追加
	for (auto& com : components_) {
		deadComponents.push_back(com);
	}

	// 削除対象リスト内のコンポーネントを安全に削除
	for (auto& com : deadComponents) {
		delete com;
	}

	// ゲームオブジェクトリストをクリア
	components_.clear();

	// オブジェクトリストから自身を削除
	game_manager_->RemoveGameObject(this);
}


//--------------------------------------------------
//	更新処理
//--------------------------------------------------
void GameObject::Update(void)
{
	if (state_ == State::Active)
	{
		UpdateComponents();		// コンポーネントの更新
		UpdateGameObject();		// オブジェクトの更新
	}
}

//--------------------------------------------------
// コンポーネントの初期化処理
//--------------------------------------------------
void GameObject::InitComponent(void)
{
	for (auto& com : components_)
	{
		com->Init();
	}
}

//--------------------------------------------------
// コンポーネントの更新処理
//--------------------------------------------------
void GameObject::UpdateComponents(void)
{
	for (auto& com : components_)
	{
		com->SetDeltaTime(delta_time_);
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