//==================================================
// [Stage1_3Scene.h] �X�e�[�W1-3�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-3���Ǘ�������N���X
//==================================================
#ifndef STAGE1_3SCENE_H_
#define STAGE1_3SCENE_H_
/*----- �C���N���[�h -----*/
#include "SceneBase.h"
//--------------------------------------------------
// �X�e�[�W1-3�V�[���N���X
//--------------------------------------------------
class Stage1_3Scene : public SceneBase
{
public:
	Stage1_3Scene(GameManager* _gameManager);
	~Stage1_3Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;
};

#endif // STAGE1_3SCENE_H_