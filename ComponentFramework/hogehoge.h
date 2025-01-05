//==================================================
// [HogeComponent.h] Hogeコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：Hogeコンポーネント
//==================================================
#ifndef HOGE_COMPONENT_H_
#define HOGE_COMPONENT_H_
/*----- インクルード -----*/
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEコンポーネント
//--------------------------------------------------
class hogehoge
{
    hogehoge(GameObject* _owner, int _updateOrder = 50);
    ~hogehoge();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::HogeComponent; }

};
#endif // HOGE_COMPONENT_H_
