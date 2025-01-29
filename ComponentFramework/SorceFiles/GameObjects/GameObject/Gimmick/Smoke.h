//=================================================================
// [SmokePipe.h] 煙ギミックの煙本体のヘッダ
// 著者：中谷凌也
//-----------------------------------------------------------------
// 説明：煙の定義
//=================================================================

#pragma once
#include "../../GameObject.h"

class Smoke : public GameObject
{
public:
	Smoke(GameManager* _gameManager,GameObject* _ownerObj, float _gimmickSize);
	~Smoke(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;
	
	auto GetSize() { return m_gimmickSize; }
	auto GetOwnerObj() { return m_ownerObj; }

	TypeID GetType(void) override { return TypeID::Smoke; }
private:
	GameObject* m_ownerObj;
	float m_gimmickSize;	// ギミックのサイズ
	float m_smokeSize;

	class SpriteComponent* sprite_component_{};					// スプライト
	class ColliderBaseComponent* collider_component_{};			// 当たり判定
	class ColliderEventComponent* collider_event_component_{};	// 当たり判定イベント
	class AnimationComponent* animation_component_{};			// アニメーションコン
};