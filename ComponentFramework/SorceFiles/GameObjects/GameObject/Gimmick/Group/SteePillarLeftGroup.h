//=================================================================
// [SteePillarLeftGroup.h] ���S���̃^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F���S���^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef STEE_PILLAE_LEFT_GROUP_H_
#define STEE_PILLAE_LEFT_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- �O���錾 -----*/
//--------------------------------------------------
// ���S���^�C�����Ǘ�����O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarLeftGroup : public GameObject
{
public:
	SteePillarLeftGroup(GameManager* _gameManager);
	~SteePillarLeftGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarLeftGroup; }

	void AddSteePillarLeftTile(GameObject* _tile);					// �O���[�v�Ƀ^�C����ǉ�
private:
	class TimerComponent* timer_component_;				// �^�C�}�[�R���|�[�l���g
	// �O���[�v�P�̂��Ǘ����Ă������
	std::vector<GameObject*> steePillarLeftTiles_;			// �O���[�v���Ǘ��������^�C��
};
#endif // STEE_PILLAE_LEFT_GROUP_H_

