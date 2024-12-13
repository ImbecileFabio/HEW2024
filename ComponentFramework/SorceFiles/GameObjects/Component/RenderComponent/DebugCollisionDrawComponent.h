//==================================================
// [DebugCollisionDrawComponent.h] 当たり判定描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：デバッグ用の描画コンポーネントの宣言
//==================================================
#ifndef DEBUG_COLLISION_DRAW_COMPONENT_H_
#define DEBUG_COLLISION_DRAW_COMPONENT_H_

/*----- インクルード -----*/
#include <string>

#include "../RenderComponent.h"
#include "../../../SubSystem/VertexBuffer.h"
#include "../../../SubSystem/IndexBuffer.h"
#include "../../../SubSystem/Shader.h"


using namespace DirectX::SimpleMath;

/*----- 構造体定義 -----*/
struct GeometryShaderBuffer {
	DirectX::XMFLOAT4X4 viewProjMatrix;	// ビュー・プロジェクション行列
	float thickness;					// 線の太さ	
	float padding[3];					// 16バイトアライメント用
};

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------
// 描画クラス
//--------------------------------------------------
class DebugCollisionDrawComponent :
	public RenderComponent
{
public:
	DebugCollisionDrawComponent(GameObject* _owner,int _drawOrder = 90);
	~DebugCollisionDrawComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw();


	//TypeID GetComponentType(void) const override { return TypeID::DebugCollisionDrawComponent; }

private:
	// 当たり判定描画
	void DrawLine(const Vector2& _start, const Vector2& _end, const Color& _color, const float& _tickness);

	ID3D11Buffer* constant_buffer_ = nullptr;	// 定数バッファ


};
#endif	// DEBUG_COLLISION_DRAW_COMPONENT_H_