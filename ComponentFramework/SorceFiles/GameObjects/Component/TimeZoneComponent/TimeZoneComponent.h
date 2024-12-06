//==================================================
// [TimeZoneComponent.h] �������鏈�����W���[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�I�u�W�F�N�g�̃X�s�[�h�����������鏈�����s��
//==================================================
#ifndef TIME_ZONE_COMPONENT_H_
#define TIME_ZONE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
/*----- �O���錾 -----*/
class ColliderBaseComponent;
class RigidbodyComponent;
//--------------------------------------------------
// �^�C���]�[�������N���X�@�����͂���H
//--------------------------------------------------
class TimeZoneComponent final : public Component
{
public:
	TimeZoneComponent(GameObject* _owner, int _updateOrder = 50);
	~TimeZoneComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	TypeID GetComponentType(void) const override { return TypeID::TimeZoneComponent; }
private:
	// �^�C���]�[�����������I�u�W�F�N�g�̓����蔻����Q�ƂŎ���
	ColliderBaseComponent* colliderComponent_ = {};
	RigidbodyComponent* rigidbodyComponent_ = {};	// ���x�̒l�ɃA�N�Z�X����
};

#endif // TIME_ZONE_COMPONENT_H_