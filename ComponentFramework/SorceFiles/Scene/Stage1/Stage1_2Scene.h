//==================================================
// [Stage1_2Scene.h] �X�e�[�W1-2�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-2���Ǘ�������N���X
//==================================================
#ifndef STAGE1_2SCENE_H_
#define STAGE1_2SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// �X�e�[�W1-2�V�[���N���X
//--------------------------------------------------
class Stage1_2Scene :  public SceneBase
{
public:
	Stage1_2Scene(GameManager* _gameManager);
	~Stage1_2Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;


private:
	// �Q�[���̏��
	enum STATE {
		Game,
		Result,
		Pouse,
		Rewind
	};
	STATE state_;


};

#endif // STAGE1_2SCENE_H_