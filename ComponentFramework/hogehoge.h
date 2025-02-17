//==================================================
// [HogeComponent.h] Hogeコンポーネント
// 著者：
//--------------------------------------------------
// 説明：Hogeコンポーネント
//==================================================
#ifndef HOGE_COMPONENT_H_
#define HOGE_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// Hogeコンポーネント
//--------------------------------------------------
class HogeComponent : public Component
{
public:
    HogeComponent(GameObject* _owner, int _updateOrder = 50);
    ~HogeComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::HogeComponent; }
private:
};
#endif // HOGE_COMPONENT_H_
