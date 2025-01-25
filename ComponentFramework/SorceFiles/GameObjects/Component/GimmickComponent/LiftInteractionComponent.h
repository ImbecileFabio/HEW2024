//==================================================
// [LiftInteractionComponent.h] リフトインタラクションコンポーネント
// 著者：有馬 啓太
//--------------------------------------------------
// 説明：リフトに乗った際の挙動を実装するコンポーネント
//==================================================
#ifndef LIFT_INTERACTION_COMPONENT_H_
#define LIFT_INTERACTION_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
class Lift;

//--------------------------------------------------
// リフトインタラクションコンポーネント
//--------------------------------------------------
class LiftInteractionComponent : public Component
{
public:
    LiftInteractionComponent(class GameObject* _owner, int _updateOrder = 27);
    ~LiftInteractionComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    void SetLift(Lift* _lift) { current_lift_ = _lift; } // 現在乗っているリフトを設定

    TypeID GetComponentType(void) const override { return TypeID::LiftInteractionComponent; }
private:
    Lift* current_lift_;

};
#endif // LIFT_INTERACTION_COMPONENT_H_
