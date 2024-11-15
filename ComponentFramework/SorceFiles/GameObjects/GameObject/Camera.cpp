//==================================================
// [Camera.cpp] カメラオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラの定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "Camera.h"
#include "../Component/CameraComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Camera::Camera(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("{}", "＜Camera＞ -> new\n");

	// カメラコンポーネント
	camera_component_ = new CameraComponent(this, 0);
	
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Camera::~Camera()
{
	std::cout << std::format("{}", "＜Camera＞ -> delete\n");
	// コンポーネントの削除
	delete camera_component_;
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Camera::UpdateGameObject()
{

}
