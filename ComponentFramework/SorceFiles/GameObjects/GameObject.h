//==================================================
// [GameObject.h] ゲームオブジェクトベースヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームオブジェクトの継承元
//==================================================
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_


/*----- インクルード -----*/
#include <memory>
#include <vector>
#include <iostream>
#include <format>
#include <typeinfo>

#include "../InputManager.h"
#include "Component.h"
#include "Component/TransformComponent.h"
#include "Component/CameraComponent.h"
#include "Component/RenderComponent.h"
#include "Component/RenderComponent/SpriteComponent.h"
#include "../sound.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameManager;
class ColliderManager;
class ColliderBaseComponent;
//--------------------------------------------------
// ゲームオブジェクトクラス
//--------------------------------------------------
class GameObject
{
public:
	enum class TypeID
	{
		None = -1
		// 自分自身
		, GameObject

		// アクター（独立した役割を持つゲームオブジェクト）
		// ここに追加したゲームオブジェクトを追加していく
		, Player
		, Camera
		, Tile
		, Robot
		, Lift
		, Item
		, TimeZone
		, Pendulum		// 振り子
		, Stick			// 振り子の棒
		, WeakFloor		// 脆い床
		, SteePillar	// 鉄柱
		, Smoke			// 煙
		, Pulley		// 滑車ギミック
		// タイルを一括で管理するグループクラス
		, WeakFloorGroup// 脆い床
		, LiftGroup		// リフト
		// ゲームオブジェクトのIDの最大値
		, MAX
	};

	// ゲームオブジェクトが所有する方のID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	// オブジェクトの状態
	enum class State
	{
		None = -1
		, Active		// Updateされる
		, Paused		// Updateされない
		, Dead			// GameObjectsリストから除外される(削除はされない)
		, MAX			// 状態の最大値
	};

public:
	GameObject(GameManager* _gameManager, std::string _objectName);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Update(void);

	void InitComponent(void);
	void UpdateComponents(void);

	virtual void InitGameObject(void) {};	// オーバーライド用
	virtual void UpdateGameObject(void) {};	// オーバーライド用

	void SetDeltaTime(float _deltaTime) { delta_time_ = _deltaTime; }	// デルタタイムの設定
	auto GetDeltaTime(void) const { return delta_time_; }	// デルタタイムの取得


	// 姿勢情報の更新
	void ComputeWorldTransform();

	// ゲームオブジェクトの名前設定、取得
	void SetObjectName(std::string _objectName) { object_name_ = _objectName; }
	auto& GetObjectName() const { return object_name_; }

	// コンポーネントの追加、削除
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	//--------------------------------------------------
	// @param	取得したい component(T)
	// @brief	GameObjectの  components_からにキャストする
	// @return	見つかれば targetを	見つからなければ nullptr を返す
	//--------------------------------------------------
	template <typename T>
	inline T* GetComponent() const {

		T* target = nullptr;
		for (auto component : components_)
		{
			target = dynamic_cast<T*>(component);
			if (target) 
			{
				return target;
			}
		}
		std::cout << std::format("＜GetComponent<{}>＞ ->Component Not Found\n", typeid(T).name());
		return nullptr;
	}

	// トランスフォームを取得
	TransformComponent* GetTransformComponent() const { return transform_component_; }

	// コンポーネントリストの取得
	const auto& GetComponents() const { return components_; }

	// ゲームオブジェクトの状態の変更
	void SetState(State _state) { state_ = _state; }
	State& GetState(void) { return state_; }

	virtual TypeID GetType(void) { return TypeID::GameObject; }

	auto& GetGameManager(void) { return game_manager_; }

	// GameObject固有の衝突した後の処理
	virtual void OnCollisionEnter(GameObject* _other) {};	// 接触した時
	virtual void OnCollisionStay(GameObject* _other) {};	// 接触し続けている
	virtual void OnCollisionExit(GameObject* _other) {};	// 接触から抜けた時
protected:
	float delta_time_{};	// デルタタイム

	// GameObjectの所有者
	 GameManager* game_manager_{};

	 // オブジェクトの名前
	 std::string object_name_{};

	// GameObjectの状態
	State state_{};

	// 所有コンポーネント
	std::vector<Component*> components_{};
	
	// 姿勢情報を再計算するか
	bool re_compute_transform_{};

	// 姿勢制御コンポーネント
	TransformComponent* transform_component_{};

	// オブジェクトごとに定まるID
	static int next_object_id_;	// 生成されたときに加算される
	int		   object_id_{};

	Sound sound_;
};

#endif	// GAMEOBJECT_H_


