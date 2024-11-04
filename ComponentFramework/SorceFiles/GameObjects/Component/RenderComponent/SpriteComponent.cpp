//==================================================
// [SpriteComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include "../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../GameObject.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../../SubSystem/dx11helper.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner,const wchar_t* _imgname,  int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
{
	// テクスチャ読み込み
	HRESULT hr = DirectX::CreateWICTextureFromFileEx(Renderer::GetDevice(), Renderer::GetDeviceContext(), _imgname, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &texture_view_);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
		return;
	}

	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

	object_name_ = std::string("不明なオブジェクト");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
SpriteComponent::~SpriteComponent(void)
{
}

//--------------------------------------------------
// 名前を定義する関数
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string _objectName)
{
	object_name_ = _objectName;
}

void SpriteComponent::Draw(void)
{
	std::cout << "＜" + object_name_ + "＞ -> 描画\n";

	
}
