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

		// �Q�[���I�u�W�F�N�g��ID�̍ő�l
		, MAX
	};

	// �Q�[���I�u�W�F�N�g�����L�������ID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	// ��������Q�[���I�u�W�F�N�g��
		, Paused	// ��~����Q�[���I�u�W�F�N�g��
		, Dead		// ���ʃQ�[���I�u�W�F�N�g��

		, MAX		// ��Ԃ̍ő�l
	};

public:
	GameObject(GameManager* _gameManager);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateComponents(void);
	virtual void UpdateGameObject(void) = 0;	// �I�[�o�[���C�h�p

	// �p�����̍X�V
	void ComputeWorldTransform();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	void SetState(State _state) { state_ = _state; }
	State& GetState(void) { return state_; }

	virtual TypeID GetType(void) { return TypeID::GameObject; }	//�I�[�o�[���C�h�p

	const auto& GetComponents() const { return components_; }

	auto& GetGameManager(void) { return game_manager_; }
	/*
	* @param	�擾������Conponent(T)
	* @brief	GameObject��components_����castedComponent�ɃL���X�g����
	* @retuan	�������castedComponent��	������Ȃ���� nullptr ��Ԃ�
	*/
	//�Ȃ񂩐�΂�nullptr�Ԃ����񂾂��ǁI�I�I�I�I�I�I�I�I�I�I�I�I�I�I
	template <typename T>
	inline T* GetComponent() const {
		for (auto component : components_)
		{
			T* castedComponent = dynamic_cast<T*>(component);
			if (castedComponent) { return castedComponent; }
		}
		std::cout << std::format("��GetComponent<T>�� -> Not Found Component\n");
		return nullptr;
	}

	// ����
	const auto& GetTransformComponent() {
		return transform_component_;
	}

protected:
	// GameObject�̏��L��
	 GameManager* game_manager_{};

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
