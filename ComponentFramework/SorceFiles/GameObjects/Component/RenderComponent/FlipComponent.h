//==================================================
// [FlipComponent.h] �摜���]�R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�摜�𔽓]����R���|�[�l���g
//==================================================
#ifndef FLOP_COMPONENT_H_
#define FLOP_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// Hoge�R���|�[�l���g
//--------------------------------------------------
class FlipComponent : public Component
{
public:
    FlipComponent(GameObject* _owner, int _updateOrder = 50);
    ~FlipComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::FlipComponent; }
private:
};
#endif // FLOP_COMPONENT_H_
