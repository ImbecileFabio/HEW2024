//==================================================
// [RenderComponent.h] 描画モジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：オブジェクトの描画をする機能の宣言
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- インクルード -----*/
#include "../Component.h"

/*----- 構造体宣言 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// 描画コンポーネントのベースクラス
//--------------------------------------------------
class RenderComponent : public Component
{
public:
	RenderComponent(class GameObject* owner, int drawOrder = 100);
	~RenderComponent(void);

	TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

private:

};

#endif	// RENDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================