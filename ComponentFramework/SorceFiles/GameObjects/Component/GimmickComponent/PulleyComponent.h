//==================================================
// [PulleyComponent.h] 滑車ギミックのコンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：滑車ギミックコンポーネントの定義
//==================================================
#ifndef PULLEY_COMPONENT_H_
#define PULLEY_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 滑車ギミックコンポーネント
//--------------------------------------------------
class PulleyComponent : public Component
{
    PulleyComponent(GameObject* _owner, int _updateOrder = 50);
    ~PulleyComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::PulleyComponent; }

};
#endif // PULLEY_COMPONENT_H_
