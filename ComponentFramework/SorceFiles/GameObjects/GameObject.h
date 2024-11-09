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

		// �Q�[���I�u�W�F�N�g��ID�̍ő�l
		, MAX
	};

	// �Q�[���I�u�W�F�N�g�����L�������ID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	// ��������Q�[���I�u�W�F�N�g���H
		, Paused	// ��~����Q�[���I�u�W�F�N�g���H
		, Dead		// ���ʃQ�[���I�u�W�F�N�g���H

		, MAX		// ��Ԃ̍ő�l
	};

public:
	GameObject(class GameManager* gameManager);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateComponents(void);
	virtual void UpdateGameObject(void);	// �I�[�o�[���C�h�p

	// �p�����̍X�V
	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void SetState(State state) { state_ = state; }
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::GameObject; }	//�I�[�o�[���C�h�p

	// �R���|�[�l���g���X�g��Ԃ�
	const std::vector<class Component*>& GetComponents() const { return components_; }

	/* 
	* @param	�擾������Conponent(target)
	* @brief	Gameobject�������Ă�R���|�[�l���g���X�g����target��T��
	* @retuan	������� target ��	������Ȃ���� nullptr ��Ԃ�
	*/
	template<typename T>
	T* GetComponent() const {
		for (Component* component : components_) {
			if (T* target = dynamic_cast<T*>(component)) {
				return target;
			}
		}
		std::cout << "<GetComponent> -> nullptr���Ԃ��ꂽ\n";
		return nullptr;
	}

	// �Q�[���}�l�[�W���[��Ԃ�
	class GameManager* GetGameManager(void) { return game_manager_; }

private:
	// GameObject�̏��L��
	class GameManager* game_manager_;

	// GameObject�̏��
	State state_;

	// ���L�R���|�[�l���g
	std::vector<class Component*> components_;

	// �p������R���|�[�l���g
	class TransformComponent* transform_component_;
	// �p�������Čv�Z���邩
	bool re_compute_transform_;
};

#endif	// GAMEOBJECT_H_
//==================================================
//				End of FIle
//==================================================