//==================================================
// [GameObject.h] �Q�[���I�u�W�F�N�g�x�[�X�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���I�u�W�F�N�g�̌p����
//==================================================
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_


/*----- �C���N���[�h -----*/
#include <memory>
#include <vector>
#include <iostream>
#include <format>

#include "../InputManager.h"
#include "Component.h"
#include "Component/TransformComponent.h"
#include "Component/CameraComponent.h"
#include "Component/RenderComponent.h"
#include "Component/RenderComponent/SpriteComponent.h"


/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameManager;
class ColliderManager;
//--------------------------------------------------
// �Q�[���I�u�W�F�N�g�N���X
//--------------------------------------------------
class GameObject
{
public:
	enum class TypeID
	{
		None = -1
		// �������g
		, GameObject

		// �A�N�^�[�i�Ɨ��������������Q�[���I�u�W�F�N�g�j
		// �����ɒǉ������Q�[���I�u�W�F�N�g��ǉ����Ă���
		, Player
		, Camera
		, Pendulum
		, Tile
		, Robot

		, ColliderTestObject	// �e�X�g
		// �Q�[���I�u�W�F�N�g��ID�̍ő�l
		, MAX
	};

	// �Q�[���I�u�W�F�N�g�����L�������ID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	// �I�u�W�F�N�g�̏��
	enum class State
	{
		None = -1
		, Active	// Update�����
		, Paused	// Update����Ȃ�
		, Dead		// emplace_back�����

		, MAX		// ��Ԃ̍ő�l
	};

public:
	GameObject(GameManager* _gameManager, std::string _objectName);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateComponents(void);

	virtual void InitGameObject(void) = 0;	// �I�[�o�[���C�h�p
	virtual void UpdateGameObject(void) = 0;	// �I�[�o�[���C�h�p

	// �p�����̍X�V
	void ComputeWorldTransform();

	// �Q�[���I�u�W�F�N�g�̖��O�ݒ�A�擾
	void SetObjectName(std::string _objectName) { object_name_ = _objectName; }
	auto& GetObjectName() const { return object_name_; }

	// �R���|�[�l���g�̒ǉ��A�폜
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	//--------------------------------------------------
	// @param	�擾������Conponent(T)
	// @brief	GameObject��components_����target�ɃL���X�g����
	// @retuan	�������target��	������Ȃ���� nullptr ��Ԃ�
	//--------------------------------------------------
	template <typename T>
	inline T* GetComponent() const {

		T* target = nullptr;
		for (auto component : components_)
		{
			target = dynamic_cast<T*>(component);
			if (target) 
			{
				return target;
			}
		}
		std::cout << std::format("��GetComponent<{}>�� ->Component Not Found\n", typeid(T).name());
		return nullptr;
	}
	// �R���|�[�l���g���X�g�̎擾
	const auto& GetComponents() const { return components_; }

	// �Q�[���I�u�W�F�N�g�̏�Ԃ̕ύX
	void SetState(State _state) { state_ = _state; }
	State& GetState(void) { return state_; }

	virtual TypeID GetType(void) { return TypeID::GameObject; }

	auto& GetGameManager(void) { return game_manager_; }

	

protected:
	// GameObject�̏��L��
	 GameManager* game_manager_{};

	 // �I�u�W�F�N�g�̖��O
	 std::string object_name_{};

	// GameObject�̏��
	State state_{};

	// ���L�R���|�[�l���g
	std::vector<Component*> components_{};

	// �p�������Čv�Z���邩
	bool re_compute_transform_{};

	// �p������R���|�[�l���g
	TransformComponent* transform_component_{};
};

#endif	// GAMEOBJECT_H_
