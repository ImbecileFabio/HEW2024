//==================================================
// [GameObject.h] �Q�[���I�u�W�F�N�g�x�[�X�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���I�u�W�F�N�g�̌p����
//==================================================
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

/*----- �C���N���[�h -----*/
#include "../StdAfx.h"
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameManager;
class Component;
class TransformComponent;

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
	GameObject(std::shared_ptr<GameManager> gameManager);
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

	virtual TypeID GetType(void) const { return TypeID::GameObject; }	//�I�[�o�[���C�h�p

	// �R���|�[�l���g���X�g��Ԃ�
	const std::vector<Component*>& GetComponents() const { return components_; }

	/*
	* @param	�擾������Conponent(target)
	* @brief	Gameobject��ComponentList����target�ɃL���X�g����
	* @retuan	������� target ��	������Ȃ���� nullptr ��Ԃ�
	*/
	//�Ȃ񂩐�΂�nullptr�Ԃ����񂾂��ǁI�I�I�I�I�I�I�I�I�I�I�I�I�I�I
	template <typename T>
	inline T* GetComponent()
	{
		for (auto& component : components_)
		{
			T* target = dynamic_cast<T*>(component);

			if (target != nullptr) { return target; }
		}
		std::cout << "<GetComponent> -> nullptr���Ԃ��ꂽ\n";
		return nullptr;
	}

	// �Q�[���}�l�[�W���[��Ԃ�
	auto GetGameManager(void) { return game_manager_; }

private:
	// GameObject�̏��L��
	std::shared_ptr<GameManager> game_manager_{};

	// GameObject�̏��
	State state_{};

	// ���L�R���|�[�l���g
	std::vector<Component*> components_{};

	// �p������R���|�[�l���g
	std::shared_ptr<TransformComponent> transform_component_{};
	// �p�������Čv�Z���邩
	bool re_compute_transform_{};
};

#endif	// GAMEOBJECT_H_
