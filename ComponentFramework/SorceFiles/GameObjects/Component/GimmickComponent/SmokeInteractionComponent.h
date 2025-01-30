//==================================================
// [SmokeInteractionComponent.h] �������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�r���ǂ̉��Ƃ̂������s���R���|�[�l���g
//==================================================
#ifndef SMOKE_INTERACTION_COMPONENT_H_
#define SMOKE_INTERACTION_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"


/*----- �O���錾 -----*/
class GameObject;
class Smoke;

//--------------------------------------------------
// Hoge�R���|�[�l���g
//--------------------------------------------------
class SmokeInteractionComponent : public Component
{
public:
    SmokeInteractionComponent(GameObject* _owner, int _updateOrder = 21);
    ~SmokeInteractionComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::SmokeInteractionComponent; }

	void SetSmoke(Smoke* _smoke) { current_smoke_ = _smoke; } // ���ݏ���Ă��鉌��ݒ�
	Smoke* GetSmoke(void) { return current_smoke_; } // ���ݏ���Ă��鉌���擾

private:
	Smoke* current_smoke_;
    
};
#endif // SMOKE_INTERACTION_COMPONENT_H_
