//==================================================
// [WeakFloorComponent.h] �Ƃ����M�~�b�N�R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Ƃ����M�~�b�N�R���|�[�l���g�̒�`
//==================================================
#ifndef WEAK_FLOOR_COMPONENT_H_
#define WEAK_FLOOR_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// �Ƃ����R���|�[�l���g
//--------------------------------------------------
class WeakFloorComponent : public Component
{
public:
    WeakFloorComponent(GameObject* _owner, int _updateOrder = 50);
    ~WeakFloorComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::WeakFloorComponent; }
private:
};
#endif // WEAK_FLOOR_COMPONENT_H_
