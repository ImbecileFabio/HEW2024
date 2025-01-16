//==================================================
// [RobotMoveComponent.h] ���{�b�g�ړ��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̋����𐧌䂷��R���|�[�l���g
//==================================================

#ifndef ROBOT_MOVE_COMPONENT_H_
#define ROBOT_MOVE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <optional>
#include "SimpleMath.h"
#include "../Component.h"


/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;
class TransformComponent;
class BoxColliderComponent;

using namespace DirectX::SimpleMath;
//--------------------------------------------------
// �J�����R���|�[�l���g
//--------------------------------------------------
class RobotMoveComponent :
    public Component
{
public:
	enum class RobotMoveState {
		Idle,
		Move,
		Fall,
		OnLift
	};

    RobotMoveComponent(GameObject* _owner, int _updateOrder = 2);
    ~RobotMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

	void SetState(RobotMoveState _state) { move_state_ = _state; }

    virtual TypeID GetComponentType(void) const override { return TypeID::RobotMoveComponent; }

private:
	void UpdateWallScanCollider();	// �E�H�[���X�L�����R���C�_�[�̍X�V
	void UpdateStepScanCollider();	// �X�e�b�v�A�b�v�p�X�L�����R���C�_�[�̍X�V
	void UpdateGroundScanCollider();	// �n�ʃX�L�����R���C�_�[�̍X�V

	bool CheckWallCollision();  // �ǂƂ̓����蔻��
	bool CheckStepUp(); 		 // �i���̏�蔻��
	bool CheckGround();		 // �n�ʂ̔���

	float GetStepHeight();	// �i���̍����𒲂ׂ�

private:
    // owner�̃R���|�[�l���g���L���b�V��
	class TransformComponent* owner_transform_;
	class VelocityComponent* owner_velocity_;
	class BoxColliderComponent* owner_collider_;
	class GravityComponent* owner_gravity_;

private:// �R���|�[�l���g���ɃQ�[���I�u�W�F�N�g�Ƃ͂���@����...��邵��, �����R���|�[�l���g������ׂ�
	class GameObject* wall_scan_object_;                 // �X�L�����p�I�u�W�F�N�g
	class ScanColliderComponent* wall_scan_collider_;    // �X�L�����p�R���C�_�[
	class GameObject* step_scan_object_;                 // �X�e�b�v�A�b�v�p�I�u�W�F�N�g
	class ScanColliderComponent* step_scan_collider_;    // �X�e�b�v�A�b�v�p�R���C�_�[
	class GameObject* ground_scan_object_;               // �n�ʃX�L�����p�I�u�W�F�N�g
	class ScanColliderComponent* ground_scan_collider_;  // �n�ʃX�L�����p�R���C�_�[

private:
	RobotMoveState move_state_;

    float speed_;				    // �ړ����x
    Vector2 direction_;         	// �ړ����� ( �E:1,0 / ��:-1,0 / ��:0,1 / ��:0,-1)
	float scan_distance_;           // ���C�L���X�g�̋���
	float max_step_height_;          // �o���i���̍���
};

#endif // ROBOT_MOVE_COMPONENT_H_


