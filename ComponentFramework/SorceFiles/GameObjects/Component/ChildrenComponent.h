//==================================================
// [ChildrenComponent.h] 子オブジェクト管理ヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：タイムゾーンオブジェクト
//==================================================
#ifndef CHILDREN_COMPONENT_H_
#define CHILDREN_COMPONENT_H_
/*----- インクルード -----*/
#include "../Component.h"
#include "../../GameManager.h"

class GmaeObject;
//--------------------------------------------------
// 子オブジェクト管理クラス
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
	// 子オブジェクトリスト
	std::vector<GameObject*> children_;
	// 親オブジェクト
	GameObject* parent_ = nullptr;
};
#endif // CHILDREN_COMPONENT_H_