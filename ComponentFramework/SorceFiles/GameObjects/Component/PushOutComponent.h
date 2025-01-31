//=================================================================
// [PushOutComponent.h] 押し出しコンポーネント
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：コライダーを持っている者同士を押し出す処理を行う
//=================================================================

#ifndef PUSH_OUT_COMPONENT_H_
#define PUSH_OUT_COMPONENT_H_

/*----- インクルード -----*/
#include <DirectXMath.h>
#include <SimpleMath.h>
#include "ColliderComponent/BoxColliderComponent.h"
#include "TransformComponent.h"


//-----------------------------------------------------------------
// 押し出しコンポーネント
//-----------------------------------------------------------------
class PushOutComponent : public Component {
public:
    PushOutComponent(GameObject* _owner, int _updateOrder = 15);
    ~PushOutComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override {};

	void ResolveCollision(GameObject* _other);


	TypeID GetComponentType(void) const override { return TypeID::PushOutComponent; }

private:

};


#endif // PUSH_OUT_COMPONENT_H_