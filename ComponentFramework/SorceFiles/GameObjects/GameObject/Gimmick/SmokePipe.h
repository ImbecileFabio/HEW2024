//=================================================================
// [SmokePipe.h] 煙ギミックのヘッダ
// 著者：有馬啓太		追記：中谷凌也
//-----------------------------------------------------------------
// 説明：煙ギミックの定義
//=================================================================
#ifndef SMOKE_H_
#define SMOKE_H_
/*----- インクルード -----*/
#include "../../GameObject.h"

constexpr float BRAKE_DEFAULT_TIME = 5.0f;
/*----- 前方宣言 -----*/
//--------------------------------------------------
// Smokeオブジェクト
//--------------------------------------------------
class SmokePipe : public GameObject
{
public:
	SmokePipe(GameManager* _gameManager);
	~SmokePipe(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SmokePipe; }
private:
	int fpsCounter_ = 0;	// 時間計測用
	bool brakeFlg_ = false;	// 破壊状態フラグ

	class RenderComponent* sprite_component_1_{};					// スプライト
	class RenderComponent* sprite_component_2_{};					// スプライト
	class ColliderBaseComponent* collider_component_{};			// 当たり判定
	class ColliderEventComponent* collider_event_component_{};	// 当たり判定イベント
	class SmokeComponent* smoke_component_{};					// 煙ギミックコンポーネント

	void OnCollisionStay(GameObject* _other = nullptr);
};
#endif // SMOKE_H_
