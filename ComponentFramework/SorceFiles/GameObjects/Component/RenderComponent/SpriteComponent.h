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
#include "../../../SubSystem/VertexBuffer.h"
#include "../../../SubSystem/IndexBuffer.h"
#include "../../../SubSystem/Shader.h"
#include "../../../SubSystem/Texture.h"



/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------
// 描画クラス
//--------------------------------------------------
class SpriteComponent :
    public RenderComponent
{
public:
    SpriteComponent(class GameObject* _owner, const std::string _imgname = NULL, int _drawOrder = 100);
    ~SpriteComponent();

    void Init() override;
    void Update() override;
    void Uninit() override;
    void Draw() ;

    void SetObjectName(std::string _objectName);

    // 更新順位を返す
    int& GetDrawOrder(void) { return draw_order_; }
    // コンポーネントのIDを返す
    TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

private:
    void InitBuffers();

    int draw_order_;            // 更新順位
    std::string object_name_;   // オブジェクト名

    // バッファ
    VertexBuffer<VERTEX_3D> vertex_buffer_;
    IndexBuffer index_buffer_;

    // シェーダ
    Shader shader_;

    // テクスチャ
    Texture texture_;
};


#endif	// SPRITE_COMPONENT_H_