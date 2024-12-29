//==================================================
// [ResultScene.cpp] ���U���g�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���U���g���Ǘ�������N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "ResultScene.h"

#include "../GameManager.h"
#include "../GameObjects/GameObject/Revolution.h"
#include "../GameObjects/GameObject/Camera.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
ResultScene::ResultScene(GameManager* _gameManager)
	: SceneBase(_gameManager, "ResultScene")
{
	camera_ = new Camera(game_manager_);
	result_ = new Revolution(game_manager_, TEXTURE_PATH_"scene/result/v01/10.JPG");
	result_->GetComponent<TransformComponent>()->SetSize(1920.0f, 1080.0f);
	result_->GetComponent<TransformComponent>()->SetPosition(0.0f, 0.0f);
	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
ResultScene::~ResultScene()
{

}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void ResultScene::Init()
{

}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void ResultScene::Uninit()
{

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void ResultScene::Update()
{
	if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		game_manager_->ChangeScene(SceneName::Title);
	}
}
