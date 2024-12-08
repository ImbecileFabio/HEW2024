//==================================================
// [ResultScene.h] ���U���g�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C�g���̊Ǘ�������N���X
//==================================================
#ifndef RESULT_SCENE_H_
#define RESULT_SCENE_H_

/*----- �C���N���[�h -----*/
#include "SceneBase.h"

//--------------------------------------------------
// ���U���g�V�[���N���X
//--------------------------------------------------
class ResultScene :
	public SceneBase
{
public:
	ResultScene(GameManager* _gameManager);
	~ResultScene();

	void Init() override;
	void Uninit() override;
	void Update() override;

};

#endif  // RESULT_SCENE_H_