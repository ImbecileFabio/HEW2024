//==================================================
// [TransformComponent.h] 姿勢制御コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：姿勢制御コンポーネントのベース
//==================================================
#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

/*----- インクルード -----*/
#include <SimpleMath.h>
#include "../Component.h"
#include "../../subSystem/dx11helper.h"

using namespace DirectX::SimpleMath;
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// 姿勢制御コンポーネント
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(class GameObject* _owner, int updateOrder = 100);
	~TransformComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CallTransform(void);

	DirectX::SimpleMath::Vector3 GetPosition() { return position_; }
	DirectX::SimpleMath::Vector3 GetRotation() { return rotation_; }
	DirectX::SimpleMath::Vector3 GetScale() { return scale_; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

private:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 position_{0.f, 0.f, 0.f};
	DirectX::SimpleMath::Vector3 rotation_{0.f, 0.f, 0.f};
	DirectX::SimpleMath::Vector3 scale_{100.f, 100.f, 100.f};


};

#endif	// TRANSFORM_COMPONENT_H_