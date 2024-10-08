//==================================================
// [RenderComponent.h] 描画コンポーネントのベースコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画コンポーネントのベースのクラス定義
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- インクルード -----*/
#include "../Component.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/



//--------------------------------------------------
// テクスチャー描画クラス
//--------------------------------------------------
class RenderComponent : public Component
{
public:	
	RenderComponent(class GameObject* owner, int drawOrder = 100);
	~RenderComponent(void);

	TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

private:
protected:
};

#endif	// RENDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
