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
#include "../../SubSystem/Shader.h"
#include "../../SubSystem/Material.h"


/*----- 構造体宣言 -----*/

/*----- 前方宣言 -----*/
class GameObject;

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// 描画コンポーネントのベースクラス
//--------------------------------------------------
class RenderComponent : public Component
{
public:
	enum class State
	{
		none = -1,
		draw,
		notDraw,
	};
	RenderComponent(GameObject* _owner, int _drawOrder = 100);
	~RenderComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};
	
	virtual void Draw(void) = 0;

	// 更新順位を返す
	int& GetDrawOrder(void) { return draw_order_; }


	virtual TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

	void SetState(State _state) { state_ = _state; }
	State GetState() { return state_; }

	// 頂点データの取得
	std::vector<VERTEX_3D>& GetVertices() { return vertices_; }
	void SetVertexBuffer(std::vector<VERTEX_3D> _vertices);

protected:
	int draw_order_;	// 更新順位

	void InitBuffers(float _cutU = 1, float _cutV = 1);	// バッファの初期化

	// バッファ
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;


	Shader shader_;	// シェーダ
	std::unique_ptr<Material> material_;

	std::vector<VERTEX_3D> vertices_;	// 頂点データ

	State state_ = State::draw;	// 描画するかしないか
};

#endif	// RENDER_COMPONENT_H_