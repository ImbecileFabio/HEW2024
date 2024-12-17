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
//--------------------------------------------------
// �J�����R���|�[�l���g
//--------------------------------------------------
class RobotMoveComponent :
    public Component
{
public:
    RobotMoveComponent(GameObject* _owner, int _updateOrder = 50);
    ~RobotMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::RobotMoveComponent; }

private:
	// ���{�b�g�̋���
    void CheckTurnAround(const TransformComponent& _transform, const BoxColliderComponent& _collider);
    // �i���̍����𒲂ׂ�
    std::optional<float> ChackStepHeight(const TransformComponent& _transform, const std::vector<GameObject*> _environmentObjects);

	float speed_;		// �ړ����x
	float max_step_height_;	// �K�i�̍���
	// �ړ����� ( �E:1,0 / ��:-1,0 / ��:0,1 / ��:0,-1)
    DirectX::SimpleMath::Vector2 direction_;
	const float step_scan_distance_;	// �K�i�̍����𒲂ׂ鋗��
	const float max_step_scan_distance_;	// �K�i�̍����𒲂ׂ�ő勗��
    
    

};

#endif // ROBOT_MOVE_COMPONENT_H_


