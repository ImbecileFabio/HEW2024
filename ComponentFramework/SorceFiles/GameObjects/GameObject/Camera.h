//==================================================
// [Camera.h] カメラオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラの制御をおこなうクラス
//==================================================

#ifndef CAMERA_H_
#define CAMERA_H_
/*----- インクルード -----*/
#include <memory>

#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameManeger;
class CameraComponent;

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
	// 所有するコンポーネント
	CameraComponent* camera_component_{};
};

#endif  // CAMERA_H_