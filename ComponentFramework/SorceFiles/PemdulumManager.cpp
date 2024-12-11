//==================================================
// [PemdulumManager.cpp] 
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の管理（選択）
//==================================================

#include "PemdulumManager.h"

//--------------------------------------------------
// コンストラクタ・デストラクタ
//--------------------------------------------------
PemdulumManager::PemdulumManager(){
	Init();
}
PemdulumManager::~PemdulumManager(){
	Uninit();
}

//--------------------------------------------------
// 初期化処理・終了処理・更新処理
//--------------------------------------------------
void PemdulumManager::Init(){
	pemgulumList_ = 0;
	pSelectedObject = ;
}
void PemdulumManager::Uninit(){
}
void PemdulumManager::Update(){
	// if(スティックの入力){
	//	pSelectedObject = 内積が一定以内かつ最も近いオブジェクトのポインタを返す関数
	// }
}


//--------------------------------------------------
// 振り子をオブジェクトに追加
//--------------------------------------------------
void PemdulumManager::AddGameObject(GameObject* _object){
	pemgulumList_.push_back(_object);
}

//--------------------------------------------------
// 内積が一定以内かつ最も近いオブジェクトのポインタを返す
//--------------------------------------------------
GameObject* PemdulumManager::PemgulumSelect(float _inputStick) {
	for (auto& pemdulum : pemgulumList_) {
		
	}
}