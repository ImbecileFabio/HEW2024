//==================================================
// [StickMoveComponent.h] 振り子の棒の動きコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：内容的には振り子の動きコンポーネントと一緒
//==================================================
#ifndef STICK_MOVE_COMPONENT_H_
#define STICK_MOVE_COMPONENT_H_
/*----- インクルード -----*/
#include "../Component.h"
#include <SimpleMath.h>
/*----- 前方宣言 -----*/
class TransformComponent;
//--------------------------------------------------
// 振り子の棒の動きコンポーネント
//--------------------------------------------------
class StickMoveComponent : public Component
{
public:
	enum class LengthState
	{
		shortLength,
		normalLength,
		longLength
	};

    StickMoveComponent(GameObject* _owner, int _updateOrder = 50);
    ~StickMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::StickMoveComponent; }

	void SetPendulumTransform(TransformComponent* _pendulumTransform) { pendulum_transform_component_ = _pendulumTransform; }

    void StickInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _stickAngle);	// 振り子の初期化
	void StickPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void StickAcceleration(float _angularAcceleration);

	void StickVelocity();					// 振り子の角度に角速度を適用
	void ConversionRadian(float _angle);	// 角度をラジアンに変換

	// 角度
	void  SetStickAngle(float _stickAngle);
	float GetStickAngle();
	// 角速度
	void  SetStickVelocity(float _angularVelocity);
	float GetStickVelocity();
	// 角加速度
	void  SetStickAcceleration(float _stickAcceleration);
	float GetStickAcceleration();
	// 支点の座標
	void  SetStickFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition);
	DirectX::SimpleMath::Vector3 GetStickFulcrum();
	// 支柱の長さ
	void  SetStickLength(float _stickLength);
	float GetStickLength();

	// 振り子の停止、始動
	void StartStickMovement();
	void StopStickMovement();

	void SetStickMovement(bool _stickMovement) { stickMovement_ = _stickMovement; }
	bool GetStickMovement() { return stickMovement_; }
private:
	DirectX::SimpleMath::Vector3 stickPosition_;	// -位置
	float isStickAngle_;							// -現在の振り子の角度
	float wasStickAngle_;							// -直前の振り子の角度
	float isStickVelocity_;							// -現在の角速度
	float wasStickVelocity_;						// -直前の角速度
	float stickAcceleration_;						// -振り子の角加速度
	DirectX::SimpleMath::Vector3 fulcrumPosition_;	// -支点の座標
	float stickLength_;								// -振り子の長さ
	float stickRadian_;								// -振り子の角度（ラジアン）
	bool  turnStick_;								// -振り子の往復で処理を切り替えるためのフラグ　true：右から左　false：左から右
	float maxStickAngle_;							// -振り子の最大角度
	float maxStickVelocity_;						// -振り子の最大速度

	// -棒が動いているかどうか
	bool stickMovement_;

	// -振り子の棒の状態
	LengthState lengthState_;

	TransformComponent* pendulum_transform_component_;	// 振り子の座標を参照するコンポーネント
};
#endif // HOGE_COMPONENT_H_
