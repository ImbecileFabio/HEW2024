//==================================================
// [Tile.h] �^�C���I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F����ǂ̃^�C���I�u�W�F�N�g
//==================================================
#ifndef TILE_H_
#define TILE_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include "../GameObject.h"

/*----- �\���̒�` -----*/
//--------------------------------------------------
// �^�C���I�u�W�F�N�g
//--------------------------------------------------
class Tile
	: public GameObject
{
public:
	Tile(GameManager* _gameManager);
	~Tile(void);

	void InitGameObject	 (void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Tile; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// ���L����R���|�[�l���g
	class RenderComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};


	// �f�o�b�O�p
	class DebugColliderDrawComponent* debug_collider_draw_component_{};
};
#endif	// TILE_H_