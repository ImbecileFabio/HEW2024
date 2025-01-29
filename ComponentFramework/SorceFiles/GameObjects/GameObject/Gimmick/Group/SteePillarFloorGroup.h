//=================================================================
// [SteePillarFloorGroup.h] �Ƃ����^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�Ƃ����^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef STEE_PILLAE_FLOOR_GROUP_H_
#define STEE_PILLAE_FLOOR_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- �O���錾 -----*/
//--------------------------------------------------
// �Ƃ����^�C�����Ǘ�����O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarFloorGroup : public GameObject
{
public:
	SteePillarFloorGroup(GameManager* _gameManager);
	~SteePillarFloorGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	void SetHitTile(bool _fg) { isHitTile_ = _fg; }

	TypeID GetType(void) override { return TypeID::SteePillarFloorGroup; }

	void AddSteePillarFloorTile(GameObject* _tile);					// �O���[�v�Ƀ^�C����ǉ�
	void SetPendulumANDMovement(GameObject* _centerPendulum);		// �O���[�v�ɒ��S�̐U��q��ݒ�

	void SetSteePillarLeftGroup(class SteePillarLeftGroup* _steePillarLeftGroup);		// �����̃O���[�v��ݒ�
	void SetSteePillarRightGroup(class SteePillarRightGroup* _steePillarRightGroup);	// �E���̃O���[�v��ݒ�
	void SetHitLeft(bool _fg) { isHitLift_ = _fg; }
	void UpdateSteePillarFloorTilePositions();	// �^�C���̈ʒu�𓯊�������֐�
	void AlignSteePillarFloorTilesWithTile(float _y);
	bool GetIsHitLift_() { return isHitLift_; }
private:
	// �O���[�v�P�̂��Ǘ����Ă������
	bool isCenterMedian_ = false;						// ���S�l�𒲂ׂ����ǂ���
	bool isOddNumber_	 = false;						// ����������ǂ���
	bool isBreakStart_	 = false;
	bool isDownStart_	 = false;						
	bool isHitTile_		 = false;						// �^�C���������������ǂ���
	bool isHitLift_		 = false;						// ���t�g�������������ǂ���
	bool isPendulumDelete_ = false;						// �U��q���������ǂ���
	int tileCenterNum_ = 0;								// �^�C���̒��S�̓Y����
	int leftIndex_ = 0;
	int rightIndex_ = 0;

	GameObject* centerPendulum_ = nullptr;				// ���S�̐U��q
	std::vector<GameObject*> steePillarFloorTiles_;		// �O���[�v���Ǘ��������^�C��

	std::vector<DirectX::SimpleMath::Vector3> initialPositions_; // �e�S�����̏����ʒu

	// �L���b�V�������R���|�[�l���g
	class PendulumMovementComponent* owner_pendulum_movement_{};	// �U��q�̓���

	// �O���[�v���Ǘ����Ă������
	class SteePillarLeftGroup*  steePillarLeftGroup_  = nullptr;		// �����̃O���[�v
	class SteePillarRightGroup* steePillarRightGroup_ = nullptr;		// �E���̃O���[�v

	void CacheInitPosition();	// �����ʒu���L���b�V������֐�
	void UpdatePendulumState();	// �U��q�̏�Ԃ��X�V����֐�
	void StartFalling();		// �����������J�n����֐�	
	DirectX::SimpleMath::Vector3 GetCenterPosition();	// �^�C���̒��S�ʒu���擾����֐�
};
#endif // STEE_PILLAE_FLOOR_GROUP_H_

