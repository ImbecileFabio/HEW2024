//==================================================
// [CameraComponent.cpp] カメラコンポーネント
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
	std::cout << std::format("＜CamelaComponent＞ -> Constructor\n");

	this->Init();
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
	target_ = Vector3(0.f, 0.f, 1.f);

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
	auto transform = owner_->GetTransformComponent();
	if (transform)
	{
		auto pos = transform->GetPosition();
		view_matrix_ = DirectX::XMMatrixLookAtLH(pos, target_, up);
	}
	else
	{
		std::cout << std::format("＜CameraComponent＞ -> Default Position\n");
		view_matrix_ = DirectX::XMMatrixLookAtLH(Vector3(0, 0, -1), Vector3(0.f, 0.f, 1.f), up);
	}

	Renderer::SetViewMatrix(&view_matrix_);

	// プロジェクション行列の生成
	float nearPlane = 1.0f;		// ニアクリップ
	float farPlane = 1000.0f;	// ファークリップ

	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(GameProcess::GetWidth()), static_cast<float>(GameProcess::GetHeight()), nearPlane, farPlane);



	Renderer::SetProjectionMatrix(&projectionMatrix);
}