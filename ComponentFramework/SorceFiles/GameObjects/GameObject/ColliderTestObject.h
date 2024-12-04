//==================================================
// [TestColliderObject.h] 描画モジュールヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：当たり判定をテストするオブジェクト
//==================================================
#ifndef TEST_COLLIDER_OBJECT_H_
#define TEST_COLLIDER_OBJECT_H_
/*----- インクルード -----*/
#include <memory>
#include "../GameObject.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
class ColliderBaseComponent;
class SpriteComponent;
class CallBackManager;
class AngularVelocityComponent;
class PendulumMovementComponent;
//--------------------------------------------------
// 当たり判定テストするオブジェクト
//--------------------------------------------------
class ColliderTestObject : public GameObject
{
public:
	ColliderTestObject(GameManager* _gameManager);
	~ColliderTestObject(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::ColliderTestObject; }
	// Objectごとに衝突を検知したときの処理を書くといいはず
	void OnCollisionEnter2D(GameObject& _other) override;	// 当たり判定の全体処理
	void OnCollisionExit2D(GameObject& _other) override {};	// 当たり判定の終了処理
	void OnCollisionStay2D(GameObject& _other) override {};	// 当たり判定の継続処理
	void OnTriggerEnter2D(GameObject& _other) override {};	// トリガーの全体処理
	void OnTriggerExit2D(GameObject& _other) override {};	// トリガーの終了処理
	void OnTriggerStay2D(GameObject& _other) override {};	// トリガーの継続処理

private:
	SpriteComponent* spriteComponent_ = {};
	ColliderBaseComponent* colliderComponent_ = {};

	// ペンデュラムの動きのテスト
	AngularVelocityComponent* angVelCom_ = {};
	PendulumMovementComponent* penCom_ = {};	
	
private:

};
#endif // _TEST_COLLIDER_OBJECT_H_