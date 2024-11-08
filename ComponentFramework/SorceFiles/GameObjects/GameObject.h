//==================================================
// [GameObject.h] ゲームオブジェクトベースヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームオブジェクトの継承元
//==================================================
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

/*----- インクルード -----*/
#include "../StdAfx.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameManager;
class Component;

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

		// ゲームオブジェクトのIDの最大値
		, MAX
	};

	// ゲームオブジェクトが所有する方のID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	// 活動するゲームオブジェクトか？
		, Paused	// 停止するゲームオブジェクトか？
		, Dead		// 死ぬゲームオブジェクトか？

		, MAX		// 状態の最大値
	};

public:
	GameObject(class GameManager* gameManager);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateComponents(void);
	virtual void UpdateGameObject(void);	// オーバーライド用

	// 姿勢情報の更新
	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void SetState(State state) { state_ = state; }
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::GameObject; }	//オーバーライド用

	// コンポーネントリストを返す
	const std::vector<class Component*>& GetComponents() const { return components_; }

	/* 
	* @param	取得したいConponent(target)
	* @brief	Gameobjectがもってるコンポーネントリストからtargetを探す
	* @retuan	見つかれば target を	見つからなければ nullptr を返す
	*/
	template<typename T>
	T* GetComponent() const {
		for (Component* component : components_) {
			if (T* target = dynamic_cast<T*>(component)) {
				return target;
			}
		}
		std::cout << "<GetComponent> -> nullptrが返された\n";
		return nullptr;
	}

	// ゲームマネージャーを返す
	class GameManager* GetGameManager(void) { return game_manager_; }

private:
	// GameObjectの所有者
	class GameManager* game_manager_;

	// GameObjectの状態
	State state_;

	// 所有コンポーネント
	std::vector<class Component*> components_;

	// 姿勢制御コンポーネント
	class TransformComponent* transform_component_;
	// 姿勢情報を再計算するか
	bool re_compute_transform_;
};

#endif	// GAMEOBJECT_H_
//==================================================
//				End of FIle
//==================================================