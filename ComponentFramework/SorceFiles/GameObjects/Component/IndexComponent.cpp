//==================================================
// [IndexComponent.h] 
// 著者：有馬啓太
//--------------------------------------------------
// 説明：
//==================================================


/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "IndexComponent.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
IndexComponent::IndexComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}


//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
IndexComponent::~IndexComponent(void)
{
}

//=======================================
//初期化処理
//=======================================
void IndexComponent::Init()
{
	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	index_buffer_.Create(indices);

}
