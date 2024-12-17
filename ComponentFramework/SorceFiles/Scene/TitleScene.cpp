//==================================================
// [TitleScene.cpp] �^�C�g���V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�^�C�g���̊Ǘ�������N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "TitleScene.h"

#include "../GameManager.h"
#include "../AudioManager.h"

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
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void TitleScene::Init()
{
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void TitleScene::Uninit()
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void TitleScene::Update()
{
	//game_manager_->GetAudioManager()->Play(SoundLabel_TitleBGM);
	if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		game_manager_->ChangeScene(SceneName::Stage1_1);
		//game_manager_->GetAudioManager()->Stop(SoundLabel_TitleBGM);
	}
}
