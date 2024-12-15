//==================================================
// [RobotMoveComponent.h] ���{�b�g�ړ��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̋����𐧌䂷��R���|�[�l���g
//==================================================

#ifndef ROBOT_MOVE_COMPONENT_H_
#define ROBOT_MOVE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "SimpleMath.h"

#include "../Component.h"


/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;

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
    void CheckTurnAround(class TransformComponent& _transform, class BoxColliderComponent& _collider);

	float speed_;		// �ړ����x
	bool right_move_flg_;	// �ړ�����
	bool on_ground_flg_;	// �n�ʂɐڒn���Ă��邩
};

#endif // ROBOT_MOVE_COMPONENT_H_


