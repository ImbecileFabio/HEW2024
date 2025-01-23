//==================================================
// [DebugColliderDrawComponent.h] 当たり判定描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：デバッグ用の描画コンポーネントの宣言
//==================================================
#ifndef DEBUG_COLLISION_DRAW_COMPONENT_H_
#define DEBUG_COLLISION_DRAW_COMPONENT_H_

/*----- インクルード -----*/
#include <string>

#include "RenderComponent.h"
#include "../../../SubSystem/Shader.h"


using namespace DirectX::SimpleMath;


/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------
// 描画クラス
//--------------------------------------------------
class DebugColliderDrawComponent :
	public RenderComponent
{
public:
	DebugColliderDrawComponent(GameObject* _owner,int _drawOrder = 100);
	~DebugColliderDrawComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw();

	void InitDebugBuffers();
	//TypeID GetComponentType(void) const override { return TypeID::DebugColliderDrawComponent; }

private:

};
#endif	// DEBUG_COLLISION_DRAW_COMPONENT_H_