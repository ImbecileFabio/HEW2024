//=================================================================
// [WeakFloorGroup.h] �Ƃ����^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�Ƃ����^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef WEAK_FLOOR_GROUP_H_
#define WEAK_FLOOR_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../../GameObject.h"
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

	void SetWeakFloorBreak(bool _isBreak) { isWeakFloorBreak_ = _isBreak; }	// �Ƃ�������ꂽ���ǂ�����ݒ�

	void AddWeakFloorTile (GameObject* _tile);					// �O���[�v�Ƀ^�C����ǉ�
	void SetPendulumANDMovement(GameObject* _centerPendulum);	// �O���[�v�ɒ��S�̐U��q��ݒ�

	int GetHitCount() { return hitCount_; }

	void SetPendulumOn(bool _fg) { isPendulumOn_ = _fg; }
private:
	int hitCount_ = 0;
	class TimerComponent* timer_component_;				// �^�C�}�[�R���|�[�l���g
	// �O���[�v�P�̂��Ǘ����Ă������
	bool isWeakFloorBreak_		 = false;				// �Ƃ�������ꂽ���ǂ���
	bool isCenterMedian			 = false;				// ���S�l�𒲂ׂ����ǂ���
	bool isPendulumOn_			 = false;				// �U��q���邩�Ȃ���
	int tileCenterNum_			 = 0;					// �^�C���̒��S�̓Y����
	GameObject* centerPendulum_ = nullptr;				// ���S�̐U��q
	std::vector<GameObject*> weakFloorTiles_;			// �O���[�v���Ǘ��������^�C��

	// �L���b�V�������R���|�[�l���g
	class PendulumMovementComponent* owner_pendulum_movement_{};	// �U��q�̓���
};
#endif // WEAK_FLOOR_GROUP_H_

