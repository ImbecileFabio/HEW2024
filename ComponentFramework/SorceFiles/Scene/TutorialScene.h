//==================================================
// [TutorialScene.h] �`���[�g���A���V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`���[�g���A���̊Ǘ�������N���X
//==================================================
#ifndef TUTORIAL_SCENE_H_
#define TUTORIAL_SCENE_H_

/*----- �C���N���[�h -----*/
#include "SceneBase.h"
#include <array>
/*----- �O���錾 -----*/
class Revolution;
//--------------------------------------------------
// ���U���g�V�[���N���X
//--------------------------------------------------
class TutorialScene:
	public SceneBase
{
public:
	TutorialScene(GameManager* _gameManager);
	~TutorialScene();

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	std::function<void()> next_scene_{};	// ���̃V�[���֑J�ڂ���֐�
	class Camera* camera_{};	// �J����
	class Revolution* tutorial_scene_{};	// �Q�[�����
	class Revolution* tutorial_play_{};		// ������
};

#endif  // TUTORIAL_SCENE_H_