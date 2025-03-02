//==================================================
// [SteePillarFloorDown.h] �S���M�~�b�N�����R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�S���M�~�b�N�̗����R���|�[�l���g��`
//==================================================
#ifndef STEE_PILLAR_FLOOR_DOWN_H_
#define STEE_PILLAR_FLOOR_DOWN_H_
/*----- �C���N���[�h -----*/
#include "../../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// �S���̏������R���|�[�l���g
//--------------------------------------------------
class SteePillarFloorMove : public Component
{
public:
    // �S���̏��̈ړ����
    enum class FloorState
    {
        Up,
        Stop,
        Falling,
        OnLift,
        OnTile,
        OnLiftAndTile,
        Down,
    };
    SteePillarFloorMove(GameObject* _owner, int _updateOrder = 20);
    ~SteePillarFloorMove();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::SteePillarFloorDown; }
    
    void SetFloorState(FloorState _floorState) { floorState_ = _floorState; }
    FloorState GetFloorState() { return floorState_; }

	void SetLiftPosition(const DirectX::SimpleMath::Vector3& _liftPosition) { liftPosition_ = _liftPosition; }
	void SetTilePosition(const DirectX::SimpleMath::Vector3& _tilePosition) { tilePosition_ = _tilePosition; }

private:
    FloorState floorState_;	// �S���̏����

    class TransformComponent* owner_transform_{}; // �L���b�V�������R���|�[�l���g
    class VelocityComponent* owner_velocity_{};
    class GravityComponent* owner_gravity_{};
    class BoxColliderComponent* owner_box_collider_{};

    DirectX::SimpleMath::Vector2 direction_;    // �S�����̈ړ��������
	DirectX::SimpleMath::Vector3 liftPosition_; // ���t�g�̈ʒu
	DirectX::SimpleMath::Vector3 tilePosition_; // �^�C���̈ʒu
};
#endif // STEE_PILLAR_COMPONENT_H_
