//=================================================================
// [SteePillar.cpp] 鉄柱オブジェクトのCPP
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱オブジェクトの実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillar.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillar::SteePillar(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillar")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
SteePillar::~SteePillar(void)
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillar::InitGameObject(void)
{
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillar::UpdateGameObject(void)
{

}

