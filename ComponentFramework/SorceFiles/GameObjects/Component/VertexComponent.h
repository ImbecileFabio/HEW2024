//==================================================
// [VertexComponent.h] コライダーのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：こいつを継承して当たり判定を作る
//==================================================
#ifndef VERTEX_COMPONENT_H_
#define VERTEX_COMPONENT_H_

/*----- インクルード -----*/
#include "../Component.h"
#include "../../subSystem/IndexBuffer.h "
#include "../../subSystem/VertexBuffer.h "

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// コライダーコンポーネント
//--------------------------------------------------
class VertexComponent :
    public Component
{
public:
    VertexComponent(class GameObject* owner, int updateOrder = 100);
    ~VertexComponent(void);

    void Init();

    virtual TypeID GetComponentType() const override { return TypeID::VertexComponent; }

private:
    IndexBuffer	 index_buffer_; // インデックスバッファ
    VertexBuffer<VERTEX_3D>	vertex_buffer_; // 頂点バッファ

};



#endif	// COLLIDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
