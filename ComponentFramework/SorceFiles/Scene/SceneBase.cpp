//==================================================
// [SceneBase.cpp] �V�[���x�[�X�N���X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�V�[���̊��N���X
//==================================================

/*----- �C���N���[�h -----*/
#include <memory>
#include "SceneBase.h"

#include "../GameManager.h"
#include "../TileMapManager.h"
//--------------------------------------------------
// @param	_gameManager �V�[���̏��L��, _sceneName �V�[����
// @brief	�R���X�g���N�^
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// ���L��
	, scene_name_(_sceneName)		// �V�[����
{
	std::cout << std::format("\n[{}] -> Constructor\n", scene_name_);
	tile_map_manager_ = std::make_unique<TileMapManager>(game_manager_);
}

SceneBase::~SceneBase()
{
	std::cout << std::format("[{}] -> Destructor\n", scene_name_);




}

