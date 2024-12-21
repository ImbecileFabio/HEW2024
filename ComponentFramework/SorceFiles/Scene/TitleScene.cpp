//==================================================
// [TitleScene.cpp] �^�C�g���V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C�g���̊Ǘ�������N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "TitleScene.h"

#include "../GameManager.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
TitleScene::TitleScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "TitleScene")
{
	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
TitleScene::~TitleScene()
{
	this->Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void TitleScene::Init()
{
	sound.Init();
	sound.Play(SoundLabel_TitleBGM);
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void TitleScene::Uninit()
{
	//sound.Uninit();
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void TitleScene::Update()
{
	if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		game_manager_->ChangeScene(SceneName::Stage1_1);
		sound.Stop(SoundLabel_TitleBGM);
	}
}
