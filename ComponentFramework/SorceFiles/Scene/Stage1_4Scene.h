//==================================================
// [Stage1_4Scene.h] �X�e�[�W1-4�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-4���Ǘ�������N���X
//==================================================
#ifndef STAGE1_4SCENE_H_
#define STAGE1_4SCENE_H_
/*----- �C���N���[�h -----*/
#include "SceneBase.h"
//--------------------------------------------------
// �X�e�[�W1-4�V�[���N���X
//--------------------------------------------------
class Stage1_4Scene : public SceneBase
{
public:
	Stage1_4Scene(GameManager* _gameManager);
	~Stage1_4Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;
};

#endif // STAGE1_4SCENE_H_