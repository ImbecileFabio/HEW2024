//==================================================
// [IndexComponent.h] 
// 著者：有馬啓太
//--------------------------------------------------
// 説明：
//==================================================
#ifndef INDEX_COMPONENT_H_
#define INDEX_COMPONENT_H_

/*----- インクルード -----*/
#include "../Component.h"
#include "../../subSystem/IndexBuffer.h "

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// コライダーコンポーネント
//--------------------------------------------------
class IndexComponent :
    public Component
{
public:
    IndexComponent(class GameObject* owner, int updateOrder = 100);
    ~IndexComponent(void);

    void Init();

    virtual TypeID GetComponentType() const override { return TypeID::IndexComponent; }

private:
    IndexBuffer	 index_buffer_; // インデックスバッファ

};



#endif	// COLLIDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
