//=================================================================
// [EffectBase.h] hogehogehoge
// ���ҁF
//-----------------------------------------------------------------
// �����Fhogehogehgoe
//=================================================================
#ifndef DFFECT_BASE_H_
#define DFFECT_BASE_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�I�u�W�F�N�g
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
	class AnimationComponent* animation_component_{};	// �A�j���[�V����
	class TimerComponent* timer_component_{};	// �^�C�}�[



};
#endif // DFFECT_BASE_H_
