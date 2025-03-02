//==================================================
// [SmokeComponent.h] ���M�~�b�N�R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���M�~�b�N�̃R���|�[�l���g��`
//==================================================
#ifndef SMOKE_COMPONENT_H_
#define SMOKE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// ���M�~�b�N�R���|�[�l���g
//--------------------------------------------------
class SmokeComponent : public Component
{
public:
    SmokeComponent(GameObject* _owner, int _updateOrder = 20);
    ~SmokeComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    void SetTimeZoneONFlg(bool _flg) {timeZoneONFlg_ = _flg; }
    auto GetTimeZoneONFlg() { return timeZoneONFlg_; }
    void SetTimeZoneHitFlg(bool _flg) { timeZoneHitFlg_ = _flg; }
    auto GetTimeZoneHitFlg() { return timeZoneHitFlg_; }
    void SetTimeSpeed(float _speed) { timeSpeed_ = _speed; };
    auto GetTimeSpeed() { return timeSpeed_; }

    TypeID GetComponentType(void) const override { return TypeID::SmokeComponent; }
private:
    bool timeZoneONFlg_ = false;
    bool timeZoneHitFlg_ = false;
    float timeSpeed_ = 1.0f;
};
#endif // SMOKE_COMPONENT_H_
