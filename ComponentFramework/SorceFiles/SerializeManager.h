//==================================================
// [SerializeManager.h] �V���A���C�Y���Ǘ�����N���X�̃w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�V���A���C�Y�E�f�V���A���C�Y���Ǘ�����N���X
//==================================================
#ifndef SERIALIZE_MANAGER_H_
#define SERIALIZE_MANAGER_H_
/*----- �C���N���[�h -----*/
#include <string>
/*----- �O���錾 -----*/
class GameObject;
class Component;
//-----------------------------------------------------------------
// �V���A���C�Y�Ǘ��}�l�[�W���[�N���X
//-----------------------------------------------------------------
class SerializeManager
{
public:
	// �V���O���g���Ȃ���̂��R�s�y
	static SerializeManager& GetInstance()
	{
		static SerializeManager instance;
		return instance;
	}
	SerializeManager(const SerializeManager&) = delete;
	SerializeManager& operator=(const SerializeManager&) = delete;

	static std::string SerializeGameObject(const GameObject* _gameObject);	// �Q�[���I�u�W�F�N�g���V���A���C�Y����֐�
	static GameObject* DeserializeGameObject(const std::string& _data);

	static std::string SerializeComponent(const Component* _component);	// �R���|�[�l���g���V���A���C�Y����֐�
	static Component*  DeserializeComponent(const std::string& _data);
private:
	SerializeManager();	 //�R���X�g���N�^
	~SerializeManager(); //�f�X�g���N�^
};

#endif // SERIALIZE_MANAGER_H_

