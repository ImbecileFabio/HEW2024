//==================================================
// [TransformComponent.h] 姿勢制御コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：姿勢制御コンポーネントのベース
//==================================================
#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

/*----- インクルード -----*/
#include <memory>
#include <SimpleMath.h>

#include "../Component.h"


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
//--------------------------------------------------
// 姿勢制御コンポーネント
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(GameObject* _owner, int updateOrder = 50);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	auto& GetPosition() { return position_; }
	auto& GetRotation() { return rotation_; }
	auto& GetScale() { return scale_; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

	/////////////////////////////////////////////////////////
	// 仮でpublicにしているが、本来はprivateにする
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 rotation_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 scale_{ 1.f, 1.f, 1.f };
	/////////////////////////////////////////////////////////

private:
	//// SRT情報（姿勢情報）
	//DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };
	//DirectX::SimpleMath::Vector3 rotation_{ 0.f, 0.f, 0.f };
	//DirectX::SimpleMath::Vector3 scale_{ 1.f, 1.f, 1.f };


};

#endif	// TRANSFORM_COMPONENT_H_