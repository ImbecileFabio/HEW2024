////==================================================
//// [DebugPolygonComponent.h] デバッグ用ポリゴン描画ヘッダファイル
//// 著者：尾上莉奈
////--------------------------------------------------
//// 説明：デバッグ用ポリゴン描画のコンポーネント
////==================================================
//#ifndef DEBUG_POLYGON_COMPONENT_H_
//#define DEBUG_POLYGON_COMPONENT_H_
///*----- インクルード -----*/
//#include "../RenderComponent.h"
//#include "../../../SubSystem/VertexBuffer.h"
//#include "../../../SubSystem/IndexBuffer.h"
//#include "../../../SubSystem/Shader.h"
//#include "../../../SubSystem/Texture.h"
////--------------------------------------------------
//// デバッグ用ポリゴン描画クラス
////--------------------------------------------------
//class DebugPolygonComponent :public RenderComponent
//{
//public:
//	DebugPolygonComponent(GameObject* _owner, int _drawOrder = 0);
//	~DebugPolygonComponent();
//
//	void Init(void) override;
//	void Uninit(void) override;
//	void Update(void) override;
//
//	TypeID GetComponentType(void) const override { return TypeID::DebugPolygonComponent; }
//
//private:
//	void InitBuffers();	// バッファの初期化
//	// バッファ
//	VertexBuffer<VERTEX_3D> vertex_buffer_;
//	IndexBuffer index_buffer_;
//
//	Shader shader_;	// シェーダ
//};
//#endif // DEBUG_POLYGON_COMPONENT_H_