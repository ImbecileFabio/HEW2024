//=================================================================
// [Effect.h] �G�t�F�N�g
// ���ҁF
//-----------------------------------------------------------------
// �����F�G�t�F�N�g�𐶐�����Q�[���I�u�W�F�N�g
// �����œn�����摜���Đ�����~�܂����������
//=================================================================
#ifndef EFFECT_H_
#define EFFECT_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// �G�t�F�N�g���Đ�����I�u�W�F�N�g
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
	GameObject* owner_{};	// �G�t�F�N�g�𐶐������I�u�W�F�N�g

	class SpriteComponent* sprite_component_ {};
	class AnimationComponent* animation_component_{};	// �A�j���[�V����

	bool is_finish_{};	// �A�j���[�V�������I��������

};
#endif // EFFECT_H_
