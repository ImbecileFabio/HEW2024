//==================================================
// [RenderComponent.h] 描画モジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：オブジェクトの描画をする機能の宣言
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- インクルード -----*/
#include <memory>

#include "../Component.h"
/*----- 構造体宣言 -----*/

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------------------
// 描画コンポーネントのベースクラス
//--------------------------------------------------
class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* _owner, int _drawOrder = 50);
	~RenderComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	virtual TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

private:

};

#endif	// RENDER_COMPONENT_H_