//==================================================
// [HogeComponent.h] Hoge�R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����FHoge�R���|�[�l���g
//==================================================
#ifndef HOGE_COMPONENT_H_
#define HOGE_COMPONENT_H_
/*----- �C���N���[�h -----*/
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�R���|�[�l���g
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
