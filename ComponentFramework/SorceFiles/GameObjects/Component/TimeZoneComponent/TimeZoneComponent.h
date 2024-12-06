//==================================================
// [TimeZoneComponent.h] 減速する処理モジュールヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：オブジェクトのスピードを減速させる処理を行う
//==================================================
#ifndef TIME_ZONE_COMPONENT_H_
#define TIME_ZONE_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
class ColliderBaseComponent;
class RigidbodyComponent;
//--------------------------------------------------
// タイムゾーン処理クラス　加速はする？
//--------------------------------------------------
class TimeZoneComponent final : public Component
{
public:
	TimeZoneComponent(GameObject* _owner, int _updateOrder = 50);
	~TimeZoneComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	TypeID GetComponentType(void) const override { return TypeID::TimeZoneComponent; }
private:
	// タイムゾーンが入ったオブジェクトの当たり判定を参照で持つよ
	ColliderBaseComponent* colliderComponent_ = {};
	RigidbodyComponent* rigidbodyComponent_ = {};	// 速度の値にアクセスする
};

#endif // TIME_ZONE_COMPONENT_H_