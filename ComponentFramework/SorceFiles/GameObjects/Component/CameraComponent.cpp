//==================================================
// [CameraComponent.c@@] カメラコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラコンポーネントの定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
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
	auto pos = Vector3(0.f, -10.f, 0.f);
	target_ = Vector3(0.f, 0.f, 0.f);

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CameraComponent::~CameraComponent()
{
	std::cout << "＜CamelaComponent＞ -> 破棄\n";

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
	view_matrix_ = DirectX::XMMatrixLookAtLH(GetOwner()->GetComponent<TransformComponent>()->GetPosition(), target_, up);

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

