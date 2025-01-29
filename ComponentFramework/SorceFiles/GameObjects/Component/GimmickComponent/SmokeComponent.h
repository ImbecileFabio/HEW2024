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

    void SetTimeZoneFlg(bool _flg) {timeZoneFlg_ = _flg; }
    auto GetTimeZoneFlg() { return timeZoneFlg_; }
    void SetTimeSpeed(float _speed) { timeSpeed_ = _speed; };
    auto GetTimeSpeed() { return timeSpeed_; }

    TypeID GetComponentType(void) const override { return TypeID::SmokeComponent; }
private:
    bool timeZoneFlg_ = false;
    float timeSpeed_ = 1.0f;
};
#endif // SMOKE_COMPONENT_H_
