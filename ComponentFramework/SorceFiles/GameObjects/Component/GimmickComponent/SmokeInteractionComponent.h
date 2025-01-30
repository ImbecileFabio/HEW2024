//==================================================
// [SmokeInteractionComponent.h] 煙やり取りコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：排煙管の煙とのやり取りを行うコンポーネント
//==================================================
#ifndef SMOKE_INTERACTION_COMPONENT_H_
#define SMOKE_INTERACTION_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"


/*----- 前方宣言 -----*/
class GameObject;
class Smoke;

//--------------------------------------------------
// Hogeコンポーネント
//--------------------------------------------------
class SmokeInteractionComponent : public Component
{
public:
    SmokeInteractionComponent(GameObject* _owner, int _updateOrder = 21);
    ~SmokeInteractionComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::SmokeInteractionComponent; }

	void SetSmoke(Smoke* _smoke) { current_smoke_ = _smoke; } // 現在乗っている煙を設定
	Smoke* GetSmoke(void) { return current_smoke_; } // 現在乗っている煙を取得

private:
	Smoke* current_smoke_;
    
};
#endif // SMOKE_INTERACTION_COMPONENT_H_
