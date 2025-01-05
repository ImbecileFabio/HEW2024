//==================================================
// [Lift.h] リフトヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトオブジェクト
//==================================================
#ifndef LIFT_H_
#define LIFT_H_
/*----- インクルード -----*/
#include "../GameObject.h"
#include <SimpleMath.h>
/*----- 前方宣言 -----*/
class Pendulum;
//--------------------------------------------------
// リフトオブジェクト
//--------------------------------------------------
class Lift : public GameObject
{
public:
	enum class MoveState
	{
		length,		// 縦移動
		side,		// 横移動
		diagonalRight,	// 斜め移動(右)
		diagonalLeft,	// 斜め移動(左)
	};
	Lift(GameManager* _gameManager);
	Lift(Lift::MoveState _moveState, float _moveDistance, GameManager* _gameManager);

	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetPendulum(Pendulum* _pendulum);
	void SetMoveState(Lift::MoveState _moveState);
private:
	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		sprite_component_		  = {};	// 画像表示
	class VelocityComponent*	velocity_component_		  = {};

	float maxMoveDistance_;								// 最大移動距離
	DirectX::SimpleMath::Vector2 traveledDistance_;		// 累積移動距離
	DirectX::SimpleMath::Vector2 direction_;			// 移動方向
	DirectX::SimpleMath::Vector3 startPos_;				// 開始位置

	Pendulum* pendulum_;					// 連動させたい振り子
	bool switchFg_;							// スイッチフラグ
	MoveState moveState_;					// 移動状態
};
#endif // _LIFT_OBJECT_H_
//class Lift : public GameObject
//{
//public:
//	enum class MoveState
//	{
//		length,		// 縦移動
//		side,		// 横移動
//		diagonal,	// 斜め移動
//	};
//	Lift(GameManager* _gameManager);
//	Lift(Lift::MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager);
//
//	~Lift(void);
//
//	void InitGameObject(void)   override;
//	void UpdateGameObject(void) override;
//
//	TypeID GetType(void) override { return TypeID::Lift; }
//	void OnCollisionEnter(GameObject* _other = nullptr) override;
//
//	void SetMaxPos(DirectX::SimpleMath::Vector3 _maxPos);
//	void SetMinPos(DirectX::SimpleMath::Vector3 _minPos);
//	void SetPendulum(Pendulum* _pendulum);
//	void SetMoveState(Lift::MoveState _moveState);
//
//private:
//	class ColliderBaseComponent* collider_base_component_ = {};
//	class EventBaseComponent* collider_event_component_ = {};
//	class RenderComponent* sprite_component_ = {};	// 画像表示
//	class VelocityComponent* velocity_component_ = {};
//
//	DirectX::SimpleMath::Vector3 maxPos_;	// 正方向の最大座標
//	DirectX::SimpleMath::Vector3 minPos_;	// 負方向の最大座標
//
//	DirectX::SimpleMath::Vector2 direction_;// 移動方向
//
//	Pendulum* pendulum_;					// 連動させたい振り子
//	bool switchFg_;							// スイッチフラグ
//	MoveState moveState_;					// 移動状態
//};