//==================================================
// [GameObject.cpp] �Q�[���I�u�W�F�N�g�̃x�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���I�u�W�F�N�g�̑匳�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include "GameObject.h"
#include "../GameManager.h"
#include "../AudioManager.h"
#include "Component/ColliderComponent/BoxColliderComponent.h"
// �I�u�W�F�N�g�̉��Z����Ă���ID
int GameObject::next_object_id_ = 0;
// �Q�[���I�u�W�F�N�g�̃��X�g
const char* GameObject::GameObjectTypeNames[static_cast<int>(TypeID::MAX)] =
{
	// �������g
	"GameObject"

	// �Q�[���I�u�W�F�N�g
	, "Player"
	, "Camera"
	, "Pendulum"
	, "Tile"
	, "Robot"
};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
GameObject::GameObject(GameManager* _gameManager, std::string _objectName, int _order)
	: game_manager_(_gameManager)	// ���L��
	, object_name_(_objectName)		// �I�u�W�F�N�g��
	, update_order_(_order)			// �X�V��q
	, state_(State::Active)			// ���
	, re_compute_transform_(true)	// �p�����̍Čv�Z
{
	// �Q�[���I�u�W�F�N�g�̓o�^
	game_manager_->AddGameObject(this);
	
	// �S�̂�ID�����Z
	next_object_id_++;
	
	// �I�u�W�F�N�g��ID��ݒ�
	object_id_ = next_object_id_;
	
	// �p������R���|�[�l���g�̒ǉ�
	transform_component_ = new TransformComponent(this);

	// �Q�[���I�u�W�F�N�g�̏�����
	this->Init();

	for (auto ObjctList : game_manager_->GetGameObjects()) {
		if (this->GetType() == ObjctList->GetType()) {
			object_fier++;
		}
	}
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
GameObject::~GameObject(void)
{
	// �Q�[���I�u�W�F�N�g�̏I������
	this->Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void GameObject::Init(void)
{
	// �R���|�[�l���g�̏�����
	this->InitComponent();
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void GameObject::Uninit(void)
{
	// �R���|�[�l���g�̍폜
	delete transform_component_;

	// �폜�Ώۃ��X�g���쐬
	std::vector<Component*> deadComponents;

	// �R���|�[�l���g���폜�Ώۃ��X�g�ɒǉ�
	for (auto& com : components_) {
		deadComponents.push_back(com);
	}

	// �폜�Ώۃ��X�g���̃R���|�[�l���g�����S�ɍ폜
	for (auto& com : deadComponents) {
		delete com;
	}

	// �Q�[���I�u�W�F�N�g���X�g���N���A
	components_.clear();

	// �I�u�W�F�N�g���X�g���玩�g���폜
	game_manager_->RemoveGameObject(this);
}


//--------------------------------------------------
//	�X�V����
//--------------------------------------------------
void GameObject::Update(void)
{
	if (state_ == State::Active)
	{
		UpdateComponents();		// �R���|�[�l���g�̍X�V
		UpdateGameObject();		// �I�u�W�F�N�g�̍X�V
	}
}

//--------------------------------------------------
// �R���|�[�l���g�̏���������
//--------------------------------------------------
void GameObject::InitComponent(void)
{
	for (auto& com : components_)
	{
		com->Init();
	}
}

//--------------------------------------------------
// �R���|�[�l���g�̍X�V����
//--------------------------------------------------
void GameObject::UpdateComponents(void)
{
	for (auto& com : components_)
	{
		com->SetDeltaTime(delta_time_);
		com->Update();
	}
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
void GameObject::AddComponent(Component* _component)
{
	int my_update_order = _component->GetUpdateOrder();

	// ���݂���ǉ������R���|�[�l���g��UpdateOrder��
	// �e�R���|�[�l���g��UpdateOrder�Ƃ��r
	// UpdateOrder�������ɂȂ�悤�ɓK���ǉ����Ă�
	auto iter = components_.begin();
	for (; iter != components_.end(); ++iter)
	{
		if (my_update_order < (*iter)->GetUpdateOrder()) { break; }
	}
	components_.insert(iter, _component);
}

//--------------------------------------------------
// �R���|�[�l���g�̍폜
//--------------------------------------------------
void GameObject::RemoveComponent(Component* _component)
{
	auto iter = std::find(components_.begin()
		, components_.end()
		, _component);	// �T���Ώ�

	if (iter != components_.end())
	{
		components_.erase(iter);	// �폜
	}
}