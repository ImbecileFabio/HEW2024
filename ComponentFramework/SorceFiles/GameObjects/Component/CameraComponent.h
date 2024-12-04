//==================================================
// [CameraComponent.h] カメラコンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：
// カメラの視野角やアス比などなど
// 2Dなのでそんな感じ
//==================================================

#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include "SimpleMath.h"

#include "../Component.h"


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------------------
// カメラコンポーネント
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