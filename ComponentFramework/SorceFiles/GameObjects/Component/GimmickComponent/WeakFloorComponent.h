//==================================================
// [WeakFloorComponent.h] �Ƃ����M�~�b�N�R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Ƃ����M�~�b�N�R���|�[�l���g�̒�`
//==================================================
#ifndef WEAK_FLOOR_COMPONENT_H_
#define WEAK_FLOOR_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../../Component.h"
#include <SimpleMath.h>
/*----- �O���錾 -----*/
//--------------------------------------------------
// �Ƃ����R���|�[�l���g
//--------------------------------------------------
class WeakFloorComponent : public Component
{
public:
    WeakFloorComponent(GameObject* _owner, int _updateOrder = 50);
    ~WeakFloorComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::WeakFloorComponent; }

    void NotSpriteDraw(void);   // �摜�̕`������Ȃ�
private:
    // owner�̃R���|�[�l���g���L���b�V��(COPY)
    class TransformComponent*    owner_transform_;
    class ColliderBaseComponent* owner_collider_;
	class RenderComponent*     owner_sprite_;
private:
    DirectX::SimpleMath::Vector2 direction_; // �ړ����� ( �E:1,0 / ��:-1,0 / ��:0,1 / ��:0,-1)
};
#endif // WEAK_FLOOR_COMPONENT_H_
