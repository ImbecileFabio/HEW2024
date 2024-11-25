//==================================================
// [ColliderTestObject.h] 当たり判定をテストするオブジェクトヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：プレイヤーの操作および制御を行うクラス
//==================================================
#ifndef COLLIDERTESTOBJECT_H_
#define COLLIDERTESTOBJECT_H_

/*----- インクルード -----*/
#include <memory>
#include <array>
#include "../GameObject.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class SpriteComponent;
class BoxColliderComponent;
//--------------------------------------------------
// 当たり判定テスト用オブジェクト
//--------------------------------------------------
class ColliderTestObject
	: public GameObject
{
public:
	ColliderTestObject(GameManager* _gameManager);
	~ColliderTestObject(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::ColliderTestObject; }

private:
	// 所有するコンポーネント
	SpriteComponent* sprite_component_{};		// スプライト
	BoxColliderComponent* box_collider_component_{};		// 当たり判定（四角）
};
#endif	// COLLIDERTESTOBJECT_H_