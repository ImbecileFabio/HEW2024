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
/*----- �萔 ------*/
constexpr int CHAPTER_MAX = 1;
constexpr int STAGE_MAX = 5;
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
		option,
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

	static int create_count;	// �^�C�g���V�[�����������ꂽ���ǂ����̃J�E���g

	int chapter_ = 0;	// ��
	int stage_	 = 0;	// �X�e�[�W
	std::array<std::array<std::function<void()>, STAGE_MAX>, CHAPTER_MAX> select_stages_;	// 5*5���̃X�e�[�W�p�Y�����z��

	void StageSelect();
	void MoveSelect();
};

#endif  // TITLE_SCENE_H_