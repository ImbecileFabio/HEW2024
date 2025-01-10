//==================================================
// [WeakFloorComponent.h] 脆い床ギミックコンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：脆い床ギミックコンポーネントの定義
//==================================================
#ifndef WEAK_FLOOR_COMPONENT_H_
#define WEAK_FLOOR_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 脆い床コンポーネント
//--------------------------------------------------
class WeakFloorComponent : public Component
{
public:
    WeakFloorComponent(GameObject* _owner, int _updateOrder = 50);
    ~WeakFloorComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::WeakFloorComponent; }
private:
};
#endif // WEAK_FLOOR_COMPONENT_H_
