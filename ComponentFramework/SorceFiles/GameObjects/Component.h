//==================================================
// [Component.h] コンポーネントベースヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：コンポーネントの大元
//==================================================
#ifndef COMPONENT_H_
#define COMPONENT_H_

/*----- インクルード -----*/
#include "GameObject.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/


//--------------------------------------------------
// コンポーネントクラス
//--------------------------------------------------
class Component
{
public:
	enum class TypeID
	{
		None = -1
		// ベースクラス
		, Component

		// ここに追加したコンポーネントを書いていく
		// レンダリング
		, RenderComponent
		, SpriteComponent

		// 姿勢制御
		, TransformComponent

		// カメラ
		, CameraComponent

		// コンポーネントの最大値
		, MAX
	};

	static const char* ComponentTypeNames[static_cast<int>(TypeID::MAX)];

public:
	Component(GameObject* gameObject, int updateOrder = 100);
	virtual ~Component();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	virtual void OnUpdateWorldTransform();

	GameObject* GetOwner(void) const { return owner_; }
	int GetUpdateOrder(void) const { return update_order_; }

	virtual TypeID GetComponentType() const = 0;

	// ロード, セーブ
	virtual void LoadProperties(void);
	virtual void SaveProperties(void);

private:
	GameObject* owner_{};	// 自分（コンポーネント）の所有者
	int update_order_{};			// 自分自身の更新順位
};


#endif	// COMPONENT_H_