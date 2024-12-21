//==================================================
// [TitleScene.h] �^�C�g���V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C�g���̊Ǘ�������N���X
//==================================================
#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

/*----- �C���N���[�h -----*/
#include "SceneBase.h"

//--------------------------------------------------
// �^�C�g���V�[���N���X
//--------------------------------------------------
class TitleScene :
    public SceneBase
{
public:
	TitleScene(GameManager* _gameManager);
	~TitleScene();

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	Sound sound;
};

#endif  // TITLE_SCENE_H_