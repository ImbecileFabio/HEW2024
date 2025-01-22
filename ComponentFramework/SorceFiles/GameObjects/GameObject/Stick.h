//==================================================
// [Stick.h] �U��q�̖_�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�U��q�̖_�N���X
//==================================================
#ifndef STICK_H_
#define STICK_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"
//--------------------------------------------------
// �R���C�_�[�̃C�x���g�������s���N���X
//--------------------------------------------------
class Stick :
    public GameObject
{
public:
    Stick(GameManager* _gameManager);
    ~Stick();

    void InitGameObject(void) override;
    void UpdateGameObject(void) override;

    TypeID GetType(void) override { return TypeID::Stick; }
private:
    class RenderComponent*           sprite_component_{};
	class StickMoveComponent*    stick_move_component_{};
};

#endif // STICK_H_