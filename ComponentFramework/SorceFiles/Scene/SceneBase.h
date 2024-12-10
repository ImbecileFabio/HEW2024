//==================================================
// [SceneBase.h] �V�[���x�[�X�N���X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�V�[���̊��N���X
//==================================================
#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

/*----- �C���N���[�h -----*/
#include <vector>
#include "../GameObjects/GameObject.h"

class GameManager;
//--------------------------------------------------
// �V�[���x�[�X�N���X
//--------------------------------------------------
class SceneBase
{
public:
	SceneBase(GameManager* _gameManager, std::string _sceneName);
	virtual ~SceneBase() {};

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;	// �V�[���؂�ւ��̏����Ƃ���Scene��Update�ɏ����������Ƃ������܂�

protected:
	 GameManager* game_manager_{};

	 std::string scene_name_{};
};

#endif  // SCENE_BASE_H_