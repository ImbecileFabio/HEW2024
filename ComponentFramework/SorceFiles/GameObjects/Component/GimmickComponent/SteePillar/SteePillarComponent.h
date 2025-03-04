//==================================================
// [SteePillarComponent.h] 鉄柱ギミックコンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：鉄柱ギミックのコンポーネント定義
//==================================================
#ifndef STEE_PILLAR_COMPONENT_H_
#define STEE_PILLAR_COMPONENT_H_
/*----- インクルード -----*/
#include "../../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEコンポーネント
//--------------------------------------------------
class SteePillarComponent : public Component
{
public:
    SteePillarComponent(GameObject* _owner, int _updateOrder = 20);
    ~SteePillarComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::SteePillarComponent; }
private:
};
#endif // STEE_PILLAR_COMPONENT_H_
