//==================================================
// [Revolution.cpp] 画像を描画するためのオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：画像を描画するためのオブジェクト
//==================================================
#ifndef REVOLUTION_H_
#define REVOLUTION_H_
/*----- インクルード -----*/
#include "../GameObject.h"
//--------------------------------------------------
// 画像を描画するためのオブジェクトクラス
//--------------------------------------------------
class Revolution :
    public GameObject
{
public:
	Revolution(GameManager* _gameManager, const std::string _imgName);
	~Revolution();

	void InitGameObject  () override;
	void UpdateGameObject() override;
private:
	class RenderComponent* sprite_component_{}; // 描画コンポーネント
};

#endif  // REVOLUTION_H_