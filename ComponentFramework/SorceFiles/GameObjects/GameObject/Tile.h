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

/*----- �O���錾 -----*/
class SpriteComponent;
class ColliderBaseComponent;
//--------------------------------------------------
// �^�C���I�u�W�F�N�g
//--------------------------------------------------
class Tile
	: public GameObject
{
public:
	Tile(GameManager* _gameManager);
	~Tile(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Tile; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// ���L����R���|�[�l���g
	SpriteComponent* sprite_component_{};
	ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};
};
#endif	// TILE_H_