//==================================================
// [SteePillarComponent.h] �S���M�~�b�N�R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�S���M�~�b�N�̃R���|�[�l���g��`
//==================================================
#ifndef STEE_PILLAR_COMPONENT_H_
#define STEE_PILLAR_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�R���|�[�l���g
//--------------------------------------------------
class SteePillarComponent : public Component
{
public:
    SteePillarComponent(GameObject* _owner, int _updateOrder = 20);
    ~SteePillarComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::SteePillarComponent; }
private:
};
#endif // STEE_PILLAR_COMPONENT_H_
