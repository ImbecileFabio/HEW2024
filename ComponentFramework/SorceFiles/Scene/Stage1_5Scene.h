//==================================================
// [Stage1_5Scene.h] �X�e�[�W1-5�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-5���Ǘ�������N���X
//==================================================
#ifndef STAGE1_5SCENE_H_
#define STAGE1_5SCENE_H_
/*----- �C���N���[�h -----*/
#include "SceneBase.h"
//--------------------------------------------------
// �X�e�[�W1-5�V�[���N���X
//--------------------------------------------------
class Stage1_5Scene : public SceneBase
{
public:
	Stage1_5Scene(GameManager* _gameManager);
	~Stage1_5Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;

	enum STATE {
		Game,
		Result,
		Pouse,
		Rewind
	};
private:
	STATE state_;
};
#endif // STAGE1_5SCENE_H_