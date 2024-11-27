//==================================================
// [PendulumComponent.cpp] �U��q���W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̏����̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <SimpleMath.h>


#include "PendulumComponent.h"
#include "../GameObject.h"
#include "../Component.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
PendulumComponent::PendulumComponent(GameObject* _owner, float _rength, float _angle, int _updateOrder)
	: Component(_owner, _updateOrder)
	, rength_(_rength)
	, angle_(_angle)
{
	std::cout << std::format("��PendulumComponent�� -> Constructor\n");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
PendulumComponent::~PendulumComponent(void)
{
	std::cout << std::format("��PendulumComponent�� -> Destructor\n");

}


//--------------------------------------------------
// �I������
//--------------------------------------------------
void PendulumComponent::Uninit()
{
}


//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void PendulumComponent::Update(void)
{

	auto transform = owner_->GetComponent<TransformComponent>();

	// �U��q�̒����ɍ��킹��
	transform->SetPosition(0, -rength_);

	// �p�x���X�V
	angle_ += 0.1f;// �����̏������������ĐU��q�̓��������
	transform->SetRotation(angle_);


	// SpriteComponent�ɓn���ƌv�Z�̏��Ԃ��Ⴄ�̂Ő�ɂ���Ƃ�
	auto r = transform->GetRotation();
	auto t = transform->GetPosition();
	auto s = transform->GetScale();
	auto rot = Matrix::CreateFromYawPitchRoll(r.y, r.x, r.z);
	auto pos = Matrix::CreateTranslation(t);
	auto scale = Matrix::CreateScale(s);
	
	Matrix mtx;
	mtx = scale * pos * rot;

	// �s�񂩂�ʒu�𒊏o
	auto mtxPos = mtx.Translation();
	transform->SetPosition(mtxPos.x, mtxPos.y);
	
	transform->SetRotation(0);

}