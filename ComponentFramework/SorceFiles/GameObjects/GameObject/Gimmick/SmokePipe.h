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
	// コンストラクタ(_gimmickSize = 煙の縦の画像比(1.0~想定))
	SmokePipe(GameManager* _gameManager, float _gimmickSize = 3.0f);
	~SmokePipe(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	void SetBreakFlg(bool _flg) { breakFlg_ = _flg; }
	auto GetBreakFlg() { return breakFlg_; }

	TypeID GetType(void) override { return TypeID::SmokePipe; }
private:
	float fpsCounter_;		// 時間計測用
	bool breakFlg_;	// 破壊状態フラグ

	GameObject* smoke_;

	class RenderComponent* sprite_component_1_{};				// スプライト
	class RenderComponent* sprite_component_2_{};				// スプライト
	class ColliderBaseComponent* collider_component_{};			// 当たり判定
	class ColliderEventComponent* collider_event_component_{};	// 当たり判定イベント
	class SmokeComponent* smoke_component_{};					// 煙ギミックコンポーネント
};
#endif // SMOKE_H_
