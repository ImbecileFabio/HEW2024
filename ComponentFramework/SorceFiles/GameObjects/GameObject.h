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

#include "../InputManager.h"
#include "Component.h"
#include "Component/TransformComponent.h"
#include "Component/CameraComponent.h"
#include "Component/RenderComponent.h"
#include "Component/RenderComponent/SpriteComponent.h"


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameManager;
class ColliderManager;
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
		, Pendulum
		, Tile

		, ColliderTestObject	// テスト
		// ゲームオブジェクトのIDの最大値
		, MAX
	};

	// ゲームオブジェクトが所有する方のID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	// 活動するゲームオブジェクトか
		, Paused	// 停止するゲームオブジェクトか
		, Dead		// 死ぬゲームオブジェクトか

		, MAX		// 状態の最大値
	};

public:
	GameObject(GameManager* _gameManager);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateComponents(void);
	virtual void UpdateGameObject(void) = 0;	// オーバーライド用

	// 姿勢情報の更新
	void ComputeWorldTransform();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	void SetState(State _state) { state_ = _state; }
	State& GetState(void) { return state_; }

	virtual TypeID GetType(void) { return TypeID::GameObject; }	//オーバーライド用

	const auto& GetComponents() const { return components_; }

	auto& GetGameManager(void) { return game_manager_; }
	/*
	* @param	取得したいConponent(T)
	* @brief	GameObjectのcomponents_からtargetにキャストする
	* @retuan	見つかればtargetを	見つからなければ nullptr を返す
	*/
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

		std::cout << std::format("＜GetComponent<T>＞ -> Not Found Component\n");
		return nullptr;
	}

protected:
	// GameObjectの所有者
	 GameManager* game_manager_{};

	// GameObjectの状態
	State state_{};

	// 所有コンポーネント
	std::vector<Component*> components_{};

	// 姿勢情報を再計算するか
	bool re_compute_transform_{};

	// 姿勢制御コンポーネント
	TransformComponent* transform_component_{};
};

#endif	// GAMEOBJECT_H_
