//==================================================
// [HogeComponent.h] Hoge�R���|�[�l���g
// ���ҁF
//--------------------------------------------------
// �����FHoge�R���|�[�l���g
//==================================================
#ifndef HOGE_COMPONENT_H_
#define HOGE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�R���|�[�l���g
//--------------------------------------------------
class hogeComponent : public Component
{
public:
    hogeComponent(GameObject* _owner, int _updateOrder = 50);
    ~hogeComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::HogeComponent; }
private:
};
#endif // HOGE_COMPONENT_H_
