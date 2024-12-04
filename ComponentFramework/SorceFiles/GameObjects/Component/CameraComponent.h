//==================================================
// [CameraComponent.h] �J�����R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F
// �J�����̎���p��A�X��ȂǂȂ�
// 2D�Ȃ̂ł���Ȋ���
//==================================================

#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include "SimpleMath.h"

#include "../Component.h"


/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------------------
// �J�����R���|�[�l���g
//--------------------------------------------------
class CameraComponent :
    public Component
{
public:
    CameraComponent(GameObject* _owner, int _updateOrder = 50);
    ~CameraComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::CameraComponent; }

private:
    DirectX::SimpleMath::Vector3 target_;
    DirectX::SimpleMath::Matrix view_matrix_;
};

#endif // CAMERA_COMPONENT_H_