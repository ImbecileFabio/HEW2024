#include "TimeZone.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
TimeZone::TimeZone(GameManager* _gameManager)
	: GameObject(_gameManager, "TimeZone")
{
	std::cout << std::format("��TimeZone�� -> Constructor\n");
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
TimeZone::~TimeZone()
{

}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void TimeZone::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void TimeZone::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief �^�C���]�[���̓����蔻��C�x���g����
//--------------------------------------------------
void TimeZone::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		// �����Ń��{�b�g�ׂ̂낵�Ă����Ȃɂ��̃X�s�[�h��ύX�H
		break;
	case GameObject::TypeID::Lift:
		break;
	default:
		break;
	}
}

