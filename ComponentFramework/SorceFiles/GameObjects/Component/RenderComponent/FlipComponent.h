//==================================================
// [FlipComponent.h] 画像反転コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：画像を反転をるコンポーネント
//==================================================
#ifndef FLOP_COMPONENT_H_
#define FLOP_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// Hogeコンポーネント
//--------------------------------------------------
class FlipComponent : public Component
{
public:
    FlipComponent(GameObject* _owner, int _updateOrder = 50);
    ~FlipComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::FlipComponent; }
private:
};
#endif // FLOP_COMPONENT_H_
