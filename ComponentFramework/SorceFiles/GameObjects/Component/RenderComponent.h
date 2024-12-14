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
#include "../../SubSystem/VertexBuffer.h"
#include "../../SubSystem/IndexBuffer.h"
#include "../../SubSystem/ConstantBuffer.h"
#include "../../SubSystem/Shader.h"

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
	
	virtual void Draw(void) = 0;

	// 更新順位を返す
	int& GetDrawOrder(void) { return draw_order_; }


	virtual TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

protected:
	int draw_order_;	// 更新順位

	void InitBuffers();	// バッファの初期化
	void InitGeometryBuffers();	// デバッグ用バッファの初期化

	// バッファ
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;
	// 定数バッファ
	ConstantBuffer<GeometryShaderBuffer> constant_buffer_;	


	Shader shader_;	// シェーダ

	std::vector<VERTEX_3D> vertices_;	// 頂点データ

};

#endif	// RENDER_COMPONENT_H_