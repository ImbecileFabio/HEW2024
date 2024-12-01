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
class ColliderComponent;
//--------------------------------------------------
// �^�C���I�u�W�F�N�g
//--------------------------------------------------
class Tile
	: public GameObject
{
public:
	Tile(GameManager* _gameManager);
	~Tile(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Tile; }

private:
	// ���L����R���|�[�l���g
	SpriteComponent* sprite_component_{};
	ColliderComponent* collider_component_{};
};
#endif	// TILE_H_