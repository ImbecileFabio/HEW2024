//==================================================
// [AngularVelocityComponent.h] �p���x���Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//		�S�D�p���x�A��]
//==================================================

#pragma once
#include "../RigidbodyComponent.h"
class AngularVelocityComponent :
    public RigidbodyComponent
{
private:
	float angularVelocity;
public:
	AngularVelocityComponent(GameObject* _owner, int _updateOrder = 50);
	~AngularVelocityComponent();
	void Init();
	void Uninit();
	void Updata();
};

