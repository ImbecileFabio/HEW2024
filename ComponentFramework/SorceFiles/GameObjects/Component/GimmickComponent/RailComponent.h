//==================================================
// [RailComponent.h] ���[���R���|�[�l���g
// ���ҁF�L�n �[��
//--------------------------------------------------
// �����F���t�g�̃��[�������̏����Ǘ�����R���|�[�l���g
//==================================================
#ifndef RAIL_COMPONENT_H_
#define RAIL_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <SimpleMath.h>
#include "../../Component.h"

/*----- �O���錾 -----*/

using namespace DirectX::SimpleMath;
//--------------------------------------------------
// ���[���R���|�[�l���g
//--------------------------------------------------
class RailComponent: public Component
{
public:
    RailComponent(GameObject* _owner, const Vector3& _startPos, const Vector3& _endPos, int _updateOrder = 50);
    ~RailComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::RailComponent; }
private:

    Vector3 start_pos_;
    Vector3 end_pos_;
};
#endif // RAIL_COMPONENT_H_
