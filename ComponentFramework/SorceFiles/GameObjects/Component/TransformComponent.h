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

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
//--------------------------------------------------
// 姿勢制御コンポーネント
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(GameObject* _owner, int updateOrder = 100);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	DirectX::SimpleMath::Vector3& GetPosition() { return position_; }
	DirectX::SimpleMath::Vector3& GetRotation() { return rotation_; }
	DirectX::SimpleMath::Vector3& GetScale() { return scale_; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) { position_ = _pos; }
	void SetRotation(DirectX::SimpleMath::Vector3 _rot) { rotation_ = _rot; }
	void SetScale(DirectX::SimpleMath::Vector3 _sca) { scale_ = _sca; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

private:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 position_{};
	DirectX::SimpleMath::Vector3 rotation_{};
	DirectX::SimpleMath::Vector3 scale_{};


};

#endif	// TRANSFORM_COMPONENT_H_