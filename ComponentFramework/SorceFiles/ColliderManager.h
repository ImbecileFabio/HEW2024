//=================================================================
// [ColiderManager.h] �R���C�_�[�}�l�[�W���[���W���[���w�b�_
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�R���C�_�[�̊Ǘ����s���N���X
//=================================================================
#ifndef COLLDIER_MANAGER_H_
#define COLLIDER_MANAGER_H_
/*----- �C���N���[�h -----*/
#include<memory>
#include<vector>
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;
//-----------------------------------------------------------------
// �R���C�_�[�}�l�[�W���[�N���X
//-----------------------------------------------------------------
class ColliderManager
{
public:
	ColliderManager(void);
	~ColliderManager(void);
	// �C���X�^���X����
	static auto Create(void) { return new ColliderManager(); }
	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* _gameObject);
	// �Q�[���I�u�W�F�N�g�̍폜
	void RemoveGameObject(GameObject* _gameObject);

	// �����蔻��̂���I�u�W�F�N�g���X�g���擾
	auto GetColliderGameObjects() const { return collider_game_objects_; }
private:
	//�X�V����
	void UpdateGameObjects(void);
	void OnColliderExit(GameObject* _gameObject);
	// �I�u�W�F�N�g���X�V�����m�F
	bool updating_game_objects_;
	std::vector<GameObject*> collider_game_objects_{};	// �����蔻��p�R���e�i
	std::vector<GameObject*> collider_out_objects_{};	// �����蔻������Ȃ��R���e�i
	std::vector<GameObject*> pending_game_objects_{};	// �ҋ@�R���e�i

};
#endif // _COLLDIER_MANAGER_H_