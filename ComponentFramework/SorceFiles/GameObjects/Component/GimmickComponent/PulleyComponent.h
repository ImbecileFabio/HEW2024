//==================================================
// [PulleyComponent.h] ���ԃM�~�b�N�̃R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���ԃM�~�b�N�R���|�[�l���g�̒�`
//==================================================
#ifndef PULLEY_COMPONENT_H_
#define PULLEY_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// ���ԃM�~�b�N�R���|�[�l���g
//--------------------------------------------------
class PulleyComponent : public Component
{
    PulleyComponent(GameObject* _owner, int _updateOrder = 50);
    ~PulleyComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::PulleyComponent; }

};
#endif // PULLEY_COMPONENT_H_
