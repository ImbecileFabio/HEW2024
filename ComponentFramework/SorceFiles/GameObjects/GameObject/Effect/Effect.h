//=================================================================
// [Effect.h] エフェクト
// 著者：
//-----------------------------------------------------------------
// 説明：エフェクトを生成するゲームオブジェクト
// 引数で渡した画像を再生する止まったら消える
//=================================================================
#ifndef EFFECT_H_
#define EFFECT_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// エフェクトを再生するオブジェクト
//--------------------------------------------------
class Effect : public GameObject
{
public:
	Effect(GameManager* _gameManager, GameObject* _owner, const std::string& _effectName);
	~Effect(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Effect; }

	auto GetIsFinish(void) { return is_finish_; }


	
private:
	GameObject* owner_{};	// エフェクトを生成したオブジェクト

	class SpriteComponent* sprite_component_ {};
	class AnimationComponent* animation_component_{};	// アニメーション

	bool is_finish_{};	// アニメーションが終了したか

};
#endif // EFFECT_H_
