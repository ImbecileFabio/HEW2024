//==================================================
// [SmokeComponent.h] 煙ギミックコンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：煙ギミックのコンポーネント定義
//==================================================
#ifndef SMOKE_COMPONENT_H_
#define SMOKE_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 煙ギミックコンポーネント
//--------------------------------------------------
class SmokeComponent : public Component
{
public:
    SmokeComponent(GameObject* _owner, int _updateOrder = 50);
    ~SmokeComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    void SetTimeZoneFlg(bool _flg) { TimeZoneFlg_ = _flg; }
    auto GetTimeZoneFlg() { return TimeZoneFlg_; }

    TypeID GetComponentType(void) const override { return TypeID::SmokeComponent; }
private:
    bool TimeZoneFlg_;
};
#endif // SMOKE_COMPONENT_H_
