//==================================================
// [TransformComponent.h] 姿勢制御コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：姿勢制御コンポーネントのベース
// Position, Rotation, Scaleの情報を持つ
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
	TransformComponent(GameObject* _owner, int updateOrder = 0);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void SetSize(const float _x, const float _y)	{ SetSize(Vector3(_x, _y, 1.0f)); }
	void SetSize(const Vector3 _size)				{ size_ = _size; }

	void SetPosition(const float _x, const float _y, const float _z = 0.0f)	{ SetPosition(Vector3(_x, _y, _z)); }
	void SetPositionY(const float _y)										{ SetPosition(Vector3(position_.x, _y, position_.z)); }
	void SetPosition(const Vector3 _position)								{ position_ = _position; }

	void SetRotation(const float _z)			{ SetRotation(Vector3(0.0f, 0.0f, _z)); }
	void SetRotation(const Vector3 _rotation)	{ rotation_ = _rotation; }

	void SetScale(const float _x,const float _y)		{ SetScale(Vector3(_x, _y, 1.0f)); };
	void SetScale(const Vector3 _scale)					{ scale_ = _scale; }


	auto GetSize()     const { return size_; }
	auto GetPosition() const { return position_; }
	auto GetRotation() const { return rotation_; }
	auto GetScale()    const { return scale_; }
	

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }


private:
	DirectX::SimpleMath::Vector3 size_{100.0f, 100.0f, 1.0f};	// サイズ

	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 position_{ 0.0f, 0.0f, 0.0f };	// 位置
	DirectX::SimpleMath::Vector3 rotation_{ 0.0f, 0.0f, 0.0f };	// 回転
	DirectX::SimpleMath::Vector3 scale_{ 1.0f, 1.0f, 1.0f };		// サイズ
};

#endif	// TRANSFORM_COMPONENT_H_