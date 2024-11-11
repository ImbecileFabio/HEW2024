//==================================================
// [Camera.h] �J�����I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����̐���������Ȃ��N���X
//==================================================

#ifndef CAMERA_H_
#define CAMERA_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class CameraComponent;

class Camera :
    public GameObject
{
public:
    Camera(GameManager* _gameManager);
    ~Camera();

    void UpdateGameObject() override;

    TypeID GetType(void) { return TypeID::Camera; }
private:
    // ��������R���|�[�l���g�������ɏ���
    std::unique_ptr<CameraComponent> camera_component_{};

};

#endif  // CAMERA_H_