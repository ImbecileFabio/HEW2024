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
	std::cout << std::format("＜Camera＞ -> new\n");

	this->InitGameObject();	
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Camera::~Camera()
{
	std::cout << std::format("＜Camera＞ -> delete\n");
	// コンポーネントの削除
	delete camera_component_;
}


//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Camera::InitGameObject(void)
{
	// カメラコンポーネント
	camera_component_ = new CameraComponent(this, 0);

	transform_component_->SetPosition(0, 0, -1);
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Camera::UpdateGameObject()
{
}
