//==================================================
// [PendulumMovementComponent.h] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//
// �\��F�U��q�^���i�p�x, �U��q�^���̒��S����̒����j�E�E�E�U��q�̈ʒu���v�Z
// �@�@�@�p�x�i�ő�p�x, 1�����̎��ԁj�E�E�E�U��q�̊p�x���v�Z�i�p���x�Ƃ����Ȃ�₩��₷��j
//==================================================

#include "../Component.h"
#include <iostream>

class PendulumMovementComponent : public Component
{
private:

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	void Update();
};