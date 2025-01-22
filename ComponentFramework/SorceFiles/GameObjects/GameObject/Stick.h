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
//--------------------------------------------------
// コライダーのイベント処理を行うクラス
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