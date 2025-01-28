//=================================================================
// [SmokePipe.h] ���M�~�b�N�̃w�b�_
// ���ҁF�L�n�[��		�ǋL�F���J����
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
class SmokePipe : public GameObject
{
public:
	// �R���X�g���N�^(_gimmickSize = ���̏c�̉摜��(1.0~�z��))
	SmokePipe(GameManager* _gameManager, float _gimmickSize = 3.0f);
	~SmokePipe(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	auto GetBrakeFlg() { return brakeFlg_; }

	TypeID GetType(void) override { return TypeID::SmokePipe; }
private:
	int fpsCounter_;		// ���Ԍv���p
	bool brakeFlg_ = false;	// �j���ԃt���O

	GameObject* smoke_;

	class RenderComponent* sprite_component_1_{};				// �X�v���C�g
	class RenderComponent* sprite_component_2_{};				// �X�v���C�g
	class ColliderBaseComponent* collider_component_{};			// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class SmokeComponent* smoke_component_{};					// ���M�~�b�N�R���|�[�l���g
};
#endif // SMOKE_H_
