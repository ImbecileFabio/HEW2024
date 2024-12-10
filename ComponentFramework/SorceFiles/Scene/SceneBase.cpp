//==================================================
// [SceneBase.cpp] �V�[���x�[�X�N���X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�V�[���̊��N���X
//==================================================

/*----- �C���N���[�h -----*/
#include "SceneBase.h"

#include "../GameManager.h"
//--------------------------------------------------
// @param	�V�[���̏��L��, �V�[����
// @brief	�R���X�g���N�^
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// ���L��
	, scene_name_(_sceneName)		// �V�[����
{
	std::cout << std::format("\n[{}] -> Constructor\n", scene_name_);
}

