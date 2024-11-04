//==================================================
// [Component.h] コンポーネントベースヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：コンポーネントの大元
//==================================================
#ifndef COMPONENT_H_
#define COMPONENT_H_

/*----- インクルード -----*/

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

		// 衝突判定
		, ColliderComponent

		// 姿勢制御
		, TransformComponent


		// コンポーネントの最大値
		, MAX
	};

	static const char* ComponentTypeNames[static_cast<int>(TypeID::MAX)];

public:
	Component(class GameObject* gameObject, int updateOrder = 100);
	virtual ~Component(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);

	virtual void OnUpdateWorldTransform();

	// 後でサブクラスが挙動を上書きできるように
	virtual void CallComponent(void) {};


	class GameObject* GetOwner(void) { return owner_; }
	int GetUpdateOrder(void) const { return update_order_; }

	virtual TypeID GetComponentType() const = 0;

	// ロード, セーブ
	virtual void LoadProperties(void);
	virtual void SaveProperties(void);

protected:
	class GameObject* owner_;	// 自分（コンポーネント）の所有者
	int update_order_;			// 自分自身の更新順位
};


#endif	// COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
