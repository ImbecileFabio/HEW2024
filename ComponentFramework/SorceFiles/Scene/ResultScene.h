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
#include <array>
/*----- �O���錾 -----*/
class Revolution;
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
private:
	class Camera*	  camera_{};	// �J����
	Revolution*		backdrop_{};	// ���U���g�̔w�i
	Revolution* result_ribbon_{};	// ���U���g�̃��{��
	std::array<Revolution*, 2> result_buttons_{};
	std::array<std::function<void()>, 2> select_button_functions_;
	int select_button_ = 0;

};

#endif  // RESULT_SCENE_H_