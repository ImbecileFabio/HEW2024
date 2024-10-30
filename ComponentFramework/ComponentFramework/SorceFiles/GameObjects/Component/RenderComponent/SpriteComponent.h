//==================================================
// [SpriteComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画コンポーネントの宣言
//==================================================
#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

/*----- インクルード -----*/
#include "../RenderComponent.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------
// 描画クラス
//--------------------------------------------------
class SpriteComponent :
    public RenderComponent
{
public:
    SpriteComponent(class GameObject* owner, int drawOrder = 100);
    ~SpriteComponent(void);

    void SetObjectName(std::string _objectName);
    void Draw(void);

    // 更新順位を返す
    int GetDrawOrder(void) { return draw_order_; }
    // コンポーネントのIDを返す
    TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

private:
    int draw_order_;            // 更新順位
    std::string object_name_;   // オブジェクト名
};


#endif	// SPRITE_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================#include "../RenderComponent.h"

