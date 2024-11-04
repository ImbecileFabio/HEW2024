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


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// 姿勢制御コンポーネント
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(class GameObject* owner, int updateOrder = 100);
	~TransformComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CallTransform(void);

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

private:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);


};

#endif	// TRANSFORM_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================

