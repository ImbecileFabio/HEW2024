//==================================================
// [PulleyComponent.cpp] 滑車ギミックコンポーネントソース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：滑車ギミックコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "PulleyComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
PulleyComponent::PulleyComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
PulleyComponent::~PulleyComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void PulleyComponent::Init()
{
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void PulleyComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void PulleyComponent::Update()
{
}
