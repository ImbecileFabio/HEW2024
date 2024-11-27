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


using namespace DirectX::SimpleMath;
//--------------------------------------------------
// 姿勢制御コンポーネント
//--------------------------------------------------
class TransformComponent : public Component
{
public:
	TransformComponent(GameObject* _owner, int updateOrder = 50);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	// Setter
	// float型
	void SetPosition(const float _x,const float _y,const float _z = 0) 
	{ position_.x = _x;	position_.y = _y;	position_.z = _z;}
	void SetRotation(const float _z)
	{ rotation_.z = _z; }
	void SetScale(const float _x,const float _y)
	{ scale_.x = _x; scale_.y = _y; }
	// Vector3型
	void SetPosition(const Vector3 _position) { position_ = _position; }
	void SetRotation(const Vector3 _rotation) { rotation_ = _rotation; }
	void SetScale(const Vector3 _scale) { scale_ = _scale; }

	// Getter
	auto& GetPosition() const { return position_; }
	auto& GetRotation() const { return rotation_; }
	auto& GetRotationZ() const {return rotation_.z;}
	auto& GetScale()    const { return scale_; }
	

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }


private:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 rotation_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 scale_{ 1.f, 1.f, 1.f };
};

#endif	// TRANSFORM_COMPONENT_H_