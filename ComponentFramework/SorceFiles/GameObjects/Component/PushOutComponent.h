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
    PushOutComponent(GameObject* _owner, int _updateOrder = 50);
    ~PushOutComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override {};

	void ResolveCollision(GameObject* _other);


	TypeID GetComponentType(void) const override { return TypeID::PushOutComponent; }

private:
    DirectX::SimpleMath::Vector3 CalculatePushOut(
        const DirectX::SimpleMath::Vector3& myPos, const DirectX::SimpleMath::Vector4& myBox,
        const DirectX::SimpleMath::Vector3& otherPos, const DirectX::SimpleMath::Vector4& otherBox
    );

    // 頻繁に呼び出すようなら最初っからownerのComponent情報をメンバ変数で持っといたほうが処理は軽いかも？
};


#endif // PUSH_OUT_COMPONENT_H_