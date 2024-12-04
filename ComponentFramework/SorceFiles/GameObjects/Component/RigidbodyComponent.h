//==================================================
// [RigidbodyComponent.h] �������Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//		�P�D�ʒu�A���x
//		�Q�D�d��
//		�R�D�Փˌ��o		�iColliderComponent�ł��I�j
//		�S�D�p���x�A��]
//		�T�D����
//		�U�D�i�f�o�b�O�j
//==================================================

#pragma once
#include "../Component.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include <iostream>
#include <format>
#include <SimpleMath.h>

class RigidbodyComponent :
    public Component
{
private:

public:
	RigidbodyComponent(GameObject* _owner, int _updateOrder = 50);
	~RigidbodyComponent();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();		// ���ׂĂ̍X�V���s��
};

