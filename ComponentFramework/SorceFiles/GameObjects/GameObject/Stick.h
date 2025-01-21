//==================================================
// [Stick.h] 振り子の棒ヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：振り子の棒クラス
//==================================================
#ifndef STICK_H_
#define STICK_H_
/*----- インクルード -----*/
#include "../GameObject.h"

/*----- 前方宣言 -----*/
class Pendulum;

//--------------------------------------------------
// コライダーのイベント処理を行うクラス
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

	// 所有者
	Pendulum* owner_pendulum_{};
};

#endif // STICK_H_