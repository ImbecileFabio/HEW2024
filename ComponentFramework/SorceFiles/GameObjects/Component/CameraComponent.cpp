//==================================================
// [CameraComponent.c@@] カメラコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラコンポーネントの定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "CameraComponent.h"
#include "../../GameProcess.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "TransformComponent.h"

/*----- ネームスペース -----*/
using namespace DirectX::SimpleMath;


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CameraComponent::CameraComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	std::format("＜CamelaComponent＞ -> Constructor\n");


	target_ = Vector3(0.f, 0.f, 0.f);

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CameraComponent::~CameraComponent()
{
	std::cout << std::format("＜CamelaComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void CameraComponent::Init()
{

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void CameraComponent::Uninit()
{
	
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void CameraComponent::Update()
{
	// ビュー変換行列作成
	Vector3 up = Vector3(0.f, 1.f, 0.f);
	// 左手系に変更
	auto transform = owner_->GetComponent<TransformComponent>();
	if (transform)
	{
		auto pos = transform->GetPosition();
		view_matrix_ = DirectX::XMMatrixLookAtLH(pos, target_, up);
	}
	else
	{
		std::cout << std::format("＜CameraComponent＞ -> Default Position\n");
		view_matrix_ = DirectX::XMMatrixLookAtLH(Vector3(0.f, 0.f, -900.f), Vector3(0.f, 0.f, 0.f), up);
	}

	Renderer::SetViewMatrix(&view_matrix_);

	// プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.f);

	float aspectRatio = static_cast<float>(GameProcess::GetWidth()) / static_cast<float>(GameProcess::GetHeight());	// アス比
	float nearPlane = 1.f;		// ニアクリップ
	float farPlane = 1000.f;	// ファークリップ

	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

