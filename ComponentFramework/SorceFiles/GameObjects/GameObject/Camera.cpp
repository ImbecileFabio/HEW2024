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

	// カメラコンポーネント
	camera_component_ = new CameraComponent(this, 0);

	transform_component_->SetPosition(0, 0, -1);
	
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
// 更新処理
//--------------------------------------------------
void Camera::UpdateGameObject()
{

	auto position = transform_component_->GetPosition();

	if (InputManager::GetInstance().GetKeyPress(VK_UP))
	{
		transform_component_->SetPosition(position.x, position.y + 1);
	}
	if (InputManager::GetInstance().GetKeyPress(VK_DOWN))
	{
		transform_component_->SetPosition(position.x, position.y - 1);
	}
	if (InputManager::GetInstance().GetKeyPress(VK_LEFT))
	{
		transform_component_->SetPosition(position.x - 1, position.y);
	}
	if (InputManager::GetInstance().GetKeyPress(VK_RIGHT))
	{
		transform_component_->SetPosition(position.x + 1, position.y);
	}

}
