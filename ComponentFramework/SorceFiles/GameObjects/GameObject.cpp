//==================================================
// [GameObject.cpp] �Q�[���I�u�W�F�N�g�̃x�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���I�u�W�F�N�g�̑匳�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include "../StdAfx.h"
#include "../GameManager.h"
#include "Component.h"
#include "GameObject.h"
#include "Component/TransformComponent.h"


// �Q�[���I�u�W�F�N�g�̃��X�g
const char* GameObject::GameObjectTypeNames[static_cast<int>(TypeID::MAX)] =
{
	// �������g
	"GameObject"

	// �A�N�^�[�i�Ɨ��������������Q�[���I�u�W�F�N�g�j
	, "Player"
	, "Camera"
};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
GameObject::GameObject(GameManager* _gameManager)
	: game_manager_(_gameManager)
	, state_(State::Active)
	, re_compute_transform_(true)
{
	// �Q�[���I�u�W�F�N�g���Ǘ���֒ǉ�
	game_manager_->AddGameObject(this);

	// �p������R���|�[�l���g�̒ǉ�
	transform_component_ = std::make_unique<TransformComponent>(this);

	// �Q�[���I�u�W�F�N�g�̏�����
	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
GameObject::~GameObject(void)
{
	this->Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void GameObject::Init(void)
{
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void GameObject::Uninit(void)
{

	game_manager_->RemoveGameObject(this);
}


//--------------------------------------------------
//	�X�V����
//--------------------------------------------------
void GameObject::Update(void)
{
	if (state_ == State::Active)
	{
		if (re_compute_transform_)
			ComputeWorldTransform();
		UpdateComponents();
		UpdateGameObject();	// �T�u�N���X��������override�ł���悤��
	}
}

//--------------------------------------------------
// �R���|�[�l���g�̍X�V����
//--------------------------------------------------
void GameObject::UpdateComponents(void)
{
	for (auto com : components_)
		com->Update();
}

//--------------------------------------------------
// �p������̍X�V
//--------------------------------------------------
void GameObject::ComputeWorldTransform()
{
	re_compute_transform_ = false;

	// �g��, ��], ���s�ړ��̏����i�[
	for (auto& com : components_)
		com->OnUpdateWorldTransform();
}

//--------------------------------------------------
// �R���|�[�l���g�̒ǉ�
//--------------------------------------------------
void GameObject::AddComponent(Component* component)
{
	int my_update_order = component->GetUpdateOrder();

	// ���݂���ǉ������R���|�[�l���g��UpdateOrder��
	// �e�R���|�[�l���g��UpdateOrder�Ƃ��r
	// UpdateOrder�����������ɂȂ�悤�ɓK���ǉ����Ă�
	auto iter = components_.begin();
	for (; iter != components_.end(); ++iter)
		if (my_update_order < (*iter)->GetUpdateOrder()) { break; }
	components_.insert(iter, component);
}

//--------------------------------------------------
// �R���|�[�l���g�̍폜
//--------------------------------------------------
void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(components_.begin()
		, components_.end()
		, component);	// �T���Ώ�

	if (iter != components_.end())
		components_.erase(iter);
}