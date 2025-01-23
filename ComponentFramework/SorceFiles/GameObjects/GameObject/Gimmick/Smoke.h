//=================================================================
// [Smoke.h] ���M�~�b�N�̃w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F���M�~�b�N�̒�`
//=================================================================
#ifndef SMOKE_H_
#define SMOKE_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"

constexpr float BRAKE_DEFAULT_TIME = 5.0f;
/*----- �O���錾 -----*/
//--------------------------------------------------
// Smoke�I�u�W�F�N�g
//--------------------------------------------------
class Smoke : public GameObject
{
public:
	Smoke(GameManager* _gameManager);
	~Smoke(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Smoke; }
private:
	int fpsCounter_ = 0;	// ���Ԍv���p
	bool brakeFlg_ = false;	// �j���ԃt���O

	class RenderComponent* sprite_component_{};					// �X�v���C�g
	class ColliderBaseComponent* collider_component_{};			// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class SmokeComponent* smoke_component_{};					// ���M�~�b�N�R���|�[�l���g
};
#endif // SMOKE_H_
