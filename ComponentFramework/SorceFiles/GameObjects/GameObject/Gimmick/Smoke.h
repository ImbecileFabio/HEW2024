//=================================================================
// [SmokePipe.h] ���M�~�b�N�̉��{�̂̃w�b�_
// ���ҁF���J����
//-----------------------------------------------------------------
// �����F���̒�`
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
	TypeID GetType(void) override { return TypeID::Smoke; }
private:
	GameObject* m_ownerObj;
	float m_gimmickSize;	// �M�~�b�N�̃T�C�Y

	void OnCollisionEnter(GameObject* _other);

	class RenderComponent* sprite_component_{};					// �X�v���C�g
	class ColliderBaseComponent* collider_component_{};			// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class AnimationComponent* animation_component_{};			// �A�j���[�V�����R��
};