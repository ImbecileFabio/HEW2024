//=================================================================
// [LiftGroup.h] ���t�g�O���[�v�I�u�W�F�N�g
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F���t�g���܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef LIFT_GROUP_H_
#define LIFT_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// ���t�g�O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class LiftGroup : public GameObject
{
public:
	LiftGroup(GameManager* _gameManager);
	~LiftGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::LiftGroup; }

	void AddLiftTile(GameObject* _tile);					// �O���[�v�Ƀ^�C����ǉ�
	void SetPendulumANDMovement(GameObject* _centerPendulum);	// �O���[�v�ɒ��S�̐U��q��ݒ�


	void UpdateLiftTilePositions(); // ���̊֐�
private:
	// �O���[�v�P�̂��Ǘ����Ă������
	bool isLeftRight_ = false;
	bool isCenterMedian = false;						// ���S�l�𒲂ׂ����ǂ���
	int tileCenterNum_ = 0;								// �^�C���̒��S�̓Y����
	int leftIndex_	   = 0;
	int rightIndex_	   = 0;
	int centerIndex_ = 0;
	GameObject* centerPendulum_ = nullptr;				// ���S�̐U��q
	std::vector<GameObject*> liftTiles_;				// �O���[�v���Ǘ��������^�C��
	std::vector<DirectX::SimpleMath::Vector3> initialPositions_; // �e���t�g�^�C���̏����ʒu

	// �L���b�V�������R���|�[�l���g
	class PendulumMovementComponent* owner_pendulum_movement_{};	// �U��q�̓���
	std::vector<class LiftComponent*>  owner_lift_components_{};	// ���t�g�R���|�[�l���g

};
#endif // LIFT_GROUP_H_
