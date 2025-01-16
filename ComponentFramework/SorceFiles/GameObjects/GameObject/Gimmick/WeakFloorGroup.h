//=================================================================
// [WeakFloorGroup.h] �Ƃ����^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�Ƃ����^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef WEAK_FLOOR_GROUP_H_
#define WEAK_FLOOR_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
#include <vector>
/*----- �O���錾 -----*/
//--------------------------------------------------
// �Ƃ����^�C�����Ǘ�����O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class WeakFloorGroup : public GameObject
{
public:
	WeakFloorGroup(GameManager* _gameManager);
	~WeakFloorGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::WeakFloorGroup; }

	void AddWeakFlootTile(GameObject* _tile);	// �O���[�v�Ƀ^�C����ǉ�
private:
	std::vector<GameObject*> weakFloorTiles_;	// �O���[�v���Ǘ��������^�C��
};
#endif // WEAK_FLOOR_GROUP_H_

