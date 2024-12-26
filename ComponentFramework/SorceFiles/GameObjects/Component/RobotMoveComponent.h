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
    RobotMoveComponent(GameObject* _owner, int _updateOrder = 50);
    ~RobotMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::RobotMoveComponent; }

private:
    // �i���̍����𒲂ׂ�
    std::optional<float> CheckStepHeight(const TransformComponent& _transform, const Vector3& _size, const std::vector<GameObject*> _environmentObjects);

	float speed_;                    // �ړ����x
	float max_step_height_;	         // ��艺��ł���i���̍���
	float step_scan_distance_;	     // �i����T������
	// �ړ����� ( �E:1,0 / ��:-1,0 / ��:0,1 / ��:0,-1)
    Vector2 direction_;
};

#endif // ROBOT_MOVE_COMPONENT_H_


