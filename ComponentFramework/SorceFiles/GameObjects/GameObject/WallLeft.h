//==================================================
// [WallLeft.h] �ǃI�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ǂ̃^�C���I�u�W�F�N�g
//==================================================
#ifndef WALL_LEFT_H_
#define WALL_LEFT_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include "../GameObject.h"

/*----- �\���̒�` -----*/
//--------------------------------------------------
// �ǃI�u�W�F�N�g
//--------------------------------------------------
class WallLeft
	: public GameObject
{
public:
	WallLeft(GameManager* _gameManager);
	~WallLeft(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Wall; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// ���L����R���|�[�l���g
	class SpriteComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};


};
#endif	// WALL_LEFT_H_