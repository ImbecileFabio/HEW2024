//==================================================
// [ColliderComponent.h] コライダーのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：だそうです
//==================================================
#ifndef COLLIDER_COMPONENT_H_
#define COLLIDER_COMPONENT_H_

/*----- インクルード -----*/
#include "../Component.h"
#include "../../subSystem/IndexBuffer.h "
#include "../../subSystem/VertexBuffer.h "

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// コライダーコンポーネント
//--------------------------------------------------
class ColliderComponent :
    public Component
{
public:
    ColliderComponent(class GameObject* owner, int updateOrder = 100);
    ~ColliderComponent(void);

    void Init();

    virtual TypeID GetComponentType() const override { return TypeID::ColliderComponent; }

private:
    IndexBuffer	 m_IndexBuffer; // インデックスバッファ
    VertexBuffer<VERTEX_3D>	m_VertexBuffer; // 頂点バッファ

};



#endif	// COLLIDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
