//==================================================
// [Camera.h] カメラオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラの制御をおこなうクラス
//==================================================

#ifndef CAMERA_H_
#define CAMERA_H_
/*----- インクルード -----*/
#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class CameraComponent;
class GameManeger;

class Camera :
    public GameObject
{
public:
    Camera(std::shared_ptr<GameManager> _gameManager);
    ~Camera();

    void UpdateGameObject() override;

    TypeID GetType(void) { return TypeID::Camera; }
private:
    // 所持するコンポーネントをここに書く
    std::shared_ptr<CameraComponent> camera_component_{};

};

#endif  // CAMERA_H_