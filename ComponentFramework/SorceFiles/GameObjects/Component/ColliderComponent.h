//==================================================
// [ColliderComponent.h] 描画モジュールヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：当たり判定のコンポーネント　試作
//==================================================
#ifndef COLLIDER_COMPONENT_H_
#define COLLIDER_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <SimpleMath.h>
#include "../Component.h"
/*----- 構造体宣言 -----*/

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------------------
// 四角形の当たり判定
//--------------------------------------------------
class BoxColliderComponent :public Component
{
public:
	BoxColliderComponent(GameObject* _owner, int _updateOrder = 50);
	~BoxColliderComponent();

	void Init  (void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CheckCollision(const DirectX::SimpleMath::Vector4& _other);

	TypeID GetComponentType(void) const override { return TypeID::BoxColliderComponent; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos)  { position_ = _pos; }
	DirectX::SimpleMath::Vector4 GetBoxSize(void) const	 { return boxSize_; }

	bool testFg;
private:
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };	// 当たり判定の原点
	DirectX::SimpleMath::Vector4 boxSize_ { 0.f, 0.f, 0.f,0.f };// 当たり判定のサイズ 上・下・左・右
};

#endif // COLLIDER_COMPONENT_H_