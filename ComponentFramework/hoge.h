//=================================================================
// [hoge.h] hogehogehoge
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����Fhogehogehgoe
//=================================================================
#ifndef HOGE_H_
#define HOGE_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�I�u�W�F�N�g
//--------------------------------------------------
class hoge : public GameObject
{
public:
	hoge(GameManager* _gameManager);
	~hoge(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::HOGE; }
private:

};
#endif // HOGE_H_
