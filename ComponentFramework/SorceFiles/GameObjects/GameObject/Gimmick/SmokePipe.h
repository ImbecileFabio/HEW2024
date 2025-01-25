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
	SmokePipe(GameManager* _gameManager);
	~SmokePipe(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SmokePipe; }
private:
	int fpsCounter_ = 0;	// ���Ԍv���p
	bool brakeFlg_ = false;	// �j���ԃt���O

	class RenderComponent* sprite_component_1_{};					// �X�v���C�g
	class RenderComponent* sprite_component_2_{};					// �X�v���C�g
	class ColliderBaseComponent* collider_component_{};			// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class SmokeComponent* smoke_component_{};					// ���M�~�b�N�R���|�[�l���g

	void OnCollisionStay(GameObject* _other = nullptr);
};
#endif // SMOKE_H_
