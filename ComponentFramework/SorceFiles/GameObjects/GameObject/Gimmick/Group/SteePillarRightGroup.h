//=================================================================
// [SteePillarRightGroup.h] �Ƃ����^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�Ƃ����^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef STEE_PILLAE_RIGHT_GROUP_H_
#define STEE_PILLAE_RIGHT_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- �O���錾 -----*/
//--------------------------------------------------
// �Ƃ����^�C�����Ǘ�����O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarRightGroup : public GameObject
{
public:
	SteePillarRightGroup(GameManager* _gameManager);
	~SteePillarRightGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRightGroup; }

	void AddSteePillarRightTile(GameObject* _tile);					// �O���[�v�Ƀ^�C����ǉ�
private:
	class TimerComponent* timer_component_;					// �^�C�}�[�R���|�[�l���g
	// �O���[�v�P�̂��Ǘ����Ă������
	std::vector<GameObject*> steePillarRightTiles_;			// �O���[�v���Ǘ��������^�C��
};
#endif // STEE_PILLAE_RIGHT_GROUP_H_

