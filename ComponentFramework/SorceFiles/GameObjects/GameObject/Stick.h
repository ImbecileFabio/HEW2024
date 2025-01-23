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

/*----- �O���錾 -----*/
class Pendulum;

//--------------------------------------------------
// �R���C�_�[�̃C�x���g�������s���N���X
//--------------------------------------------------
class Stick :
    public GameObject
{
public:
    enum class StickLengthState {
		Short,
		Middle,
		Long
	};

    Stick(GameManager* _gameManager, Pendulum* _pendulum);
    ~Stick();

    void InitGameObject(void) override;
    void UpdateGameObject(void) override;

	void SetStickLengthState(StickLengthState _state) { stick_length_state_ = _state; }
	auto GetStickLengthState() const { return stick_length_state_; }

	auto GetOwnerPendulum() const { return owner_pendulum_; }

    TypeID GetType(void) override { return TypeID::Stick; }
private:
    class RenderComponent*       sprite_component_{};
	class StickMoveComponent*    stick_move_component_{};

	StickLengthState stick_length_state_;

	// ���L��
	Pendulum* owner_pendulum_{};
};

#endif // STICK_H_