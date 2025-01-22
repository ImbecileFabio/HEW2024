//==================================================
// [GravityComponent.h] �d�̓R���|�[�l���g
// ���ҁF
//--------------------------------------------------
// �����F�d�͂̏����������Ȃ�
//  ����v���X�A�n�ʂɐڒn���Ă��邩�ǂ����̔�����Ƃ�
//==================================================
#ifndef GRAVITY_COMPONENT_H_
#define GRAVITY_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"

/*----- �O���錾 -----*/
//--------------------------------------------------
// �d�̓R���|�[�l���g
//--------------------------------------------------
class GravityComponent : public Component
{
public:
    GravityComponent(GameObject* _owner, int _updateOrder = 1);
    ~GravityComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

	// �����ɒn�ʂ����邩�ǂ����̊m�F
	bool CheckGroundCollision();

	void SetUseGravityFlg(bool _flg) { use_gravity_ = _flg; }	// �d�͎g�p�t���O�Z�b�^�[
	bool GetIsGround() const { return is_ground_; }		// 

    TypeID GetComponentType(void) const override { return TypeID::GravityComponent; }
private:

	// owner�̃R���|�[�l���g���L���b�V��
	bool is_ground_; // �n�ʂɐڒn���Ă��邩
	bool use_gravity_; // �d�͂̎g�p

	float gravity_;     // �d��
};
#endif // GRAVITY_COMPONENT_H_
