//==================================================
// [LiftInteractionComponent.h] ���t�g�C���^���N�V�����R���|�[�l���g
// ���ҁF�L�n �[��
//--------------------------------------------------
// �����F���t�g�ɏ�����ۂ̋�������������R���|�[�l���g
//==================================================
#ifndef LIFT_INTERACTION_COMPONENT_H_
#define LIFT_INTERACTION_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
class Lift;

//--------------------------------------------------
// ���t�g�C���^���N�V�����R���|�[�l���g
//--------------------------------------------------
class LiftInteractionComponent : public Component
{
public:
    LiftInteractionComponent(class GameObject* _owner, int _updateOrder = 27);
    ~LiftInteractionComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    void SetLift(Lift* _lift) { current_lift_ = _lift; } // ���ݏ���Ă��郊�t�g��ݒ�

    TypeID GetComponentType(void) const override { return TypeID::LiftInteractionComponent; }
private:
    Lift* current_lift_;

};
#endif // LIFT_INTERACTION_COMPONENT_H_
