//==================================================
// [Camera.h] �J�����I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�J�����̐���������Ȃ��N���X
//==================================================

#ifndef CAMERA_H_
#define CAMERA_H_
/*----- �C���N���[�h -----*/
#include <memory>

#include "../GameObject.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameManeger;

//==================================================
// �J�����N���X
//==================================================
class Camera
    : public GameObject
{
public:
    Camera(GameManager* _gameManager);
    ~Camera();

    void InitGameObject(void) override;
    void UpdateGameObject() override;

    TypeID GetType(void) { return TypeID::Camera; }

private:
	// ���L����R���|�[�l���g
	class CameraComponent* camera_component_{};
};

#endif  // CAMERA_H_