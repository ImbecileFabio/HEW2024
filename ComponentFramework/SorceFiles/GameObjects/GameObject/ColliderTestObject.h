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
	
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::ColliderTestObject; }
private:
	SpriteComponent* spriteComponent_ = {};
	ColliderBaseComponent* colliderComponent_ = {};

	// ペンデュラムの動きのテスト
	AngularVelocityComponent* angVelCom_ = {};
	PendulumMovementComponent* penCom_ = {};	
	
private:
	// あたり判定を持たせたいオブジェクトはColliderManagerに登録する
	// GameManagerがないとGetRenderer()が使えないぜ　RIP
	//ColliderManager* p_colliderManager_ = {};
	//CallBackManager* p_callBackManager_ = {};	// コールバックを使用したいオブジェクトに配置
};
#endif // _TEST_COLLIDER_OBJECT_H_