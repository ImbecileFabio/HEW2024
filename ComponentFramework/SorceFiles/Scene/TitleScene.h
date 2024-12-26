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
#include <array>
//--------------------------------------------------
// �^�C�g���V�[���N���X
//--------------------------------------------------
class TitleScene :
    public SceneBase
{
public:
	enum class State
	{
		none = -1, 
		title,
		select,
		max,
	};
	TitleScene(GameManager* _gameManager);
	~TitleScene();

	void Init  () override;
	void Uninit() override;
	void Update() override;
private:
	State state_;
	class Camera*	 camera_{};			// �J����
	class Revolution* title_{};
	Revolution* select_rough_{};	// �ЂƂ܂��m�F�̂��߂̃Z���N�g��ʃ��t

	std::array<std::array<int, 5>, 5> select_stages_;	// 5*5���̃X�e�[�W���X�g
};

#endif  // TITLE_SCENE_H_