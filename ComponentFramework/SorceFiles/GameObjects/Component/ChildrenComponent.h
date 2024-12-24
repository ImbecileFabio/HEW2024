//==================================================
// [ChildrenComponent.h] �q�I�u�W�F�N�g�Ǘ��w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�^�C���]�[���I�u�W�F�N�g
//==================================================
#ifndef CHILDREN_COMPONENT_H_
#define CHILDREN_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"
#include "../../GameManager.h"

class GmaeObject;
//--------------------------------------------------
// �q�I�u�W�F�N�g�Ǘ��N���X
//--------------------------------------------------
class ChildrenComponent :
    public Component
{
public:
	ChildrenComponent(GameObject* _gameObject, GameObject* _parent, int _updateOrder = 50);
	~ChildrenComponent();

	void Init  (void) override;
	void Uninit(void) override;
	void Update(void) override;

	const std::vector<GameObject*>& GetChildren() const { return children_; }
	void AddChild (GameObject* _child);
	void SetParent(GameObject* _parent) { parent_ = _parent; }

	virtual TypeID GetComponentType() const { return TypeID::ChildrenComponent; }
private:
	// �q�I�u�W�F�N�g���X�g
	std::vector<GameObject*> children_;
	// �e�I�u�W�F�N�g
	GameObject* parent_ = nullptr;
};
#endif // CHILDREN_COMPONENT_H_