//=================================================================
// [EffectBase.h] hogehogehoge
// 著者：
//-----------------------------------------------------------------
// 説明：hogehogehgoe
//=================================================================
#ifndef DFFECT_BASE_H_
#define DFFECT_BASE_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEオブジェクト
//--------------------------------------------------
class EffectBase : public GameObject
{
public:
	EffectBase(GameManager* _gameManager, std::string& _effectName);
	~EffectBase(void);

	virtual void InitGameObject(void) override;
	virtual void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::EffectBase; }

	
private:

	class SpriteComponent* sprite_component_ {};
	class AnimationComponent* animation_component_{};	// アニメーション
	class TimerComponent* timer_component_{};	// タイマー



};
#endif // DFFECT_BASE_H_
