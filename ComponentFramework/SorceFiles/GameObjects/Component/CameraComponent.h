//==================================================
// [CameraComponent.h] �J�����R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����̎���p��A�X��ȂǂȂ�
//==================================================

#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"
#include "SimpleMath.h"

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
    CameraComponent(std::shared_ptr<GameObject> _owner, int _updateOrder = 100);
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