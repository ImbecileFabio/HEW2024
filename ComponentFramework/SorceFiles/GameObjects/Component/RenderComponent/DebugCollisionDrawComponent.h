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
#include "../../../SubSystem/ConstantBuffer.h"
#include "../../../SubSystem/Shader.h"


using namespace DirectX::SimpleMath;


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


};
#endif	// DEBUG_COLLISION_DRAW_COMPONENT_H_