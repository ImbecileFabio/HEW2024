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
/*----- �O���錾 ------*/
class Revolution;
/*----- �萔 ------*/
constexpr int CHAPTER_MAX = 3;
constexpr int STAGE_MAX = 4;

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
		option,
		select,
		end,
		max,
	};
	TitleScene(GameManager* _gameManager);
	~TitleScene();

	void Init  () override;
	void Uninit() override;
	void Update() override;

	int GetCreateCount() { return create_count; }
private:
	State state_;
	class Camera*	   camera_;					// �J����
	Revolution*		 backdrop_;					// �^�C�g���ƃZ���N�g�̔w�i
	// �^�C�g������̃I�u�W�F�N�g�ƕϐ�
	Revolution* title_logo_;					// �^�C�g���̃��S
	Revolution* title_ribbon_;					// �{�^���̔w�i���{��
	Revolution* title_cursor_;					// �^�C�g���̃J�[�\��
	std::array<Revolution*, 3> title_buttons_;	// �^�C�g���̃{�^��
	int title_select_button_ = 0;				// �^�C�g���̃{�^���̓Y����
	static int create_count;					// �^�C�g���V�[�����������ꂽ���ǂ����̃J�E���g
	// �Z���N�g��ʎ���̃I�u�W�F�N�g�ƕϐ�
	Revolution* select_left_button_;			// LB�{�^��
	Revolution* select_right_button_;			// RB�{�^��
	Revolution* select_option_button_;			// �I�v�V�����{�^��
	Revolution* select_return_button_;			// �߂�{�^��
	Revolution* select_chapter_left;			// LB�{�^���ɕ\�������`���v�^�[�i���o�[
	Revolution* select_chapter_right;			// RB�{�^���ɕ\�������`���v�^�[�i���o�[
	Revolution* select_chapter_center;			// ���݂̑I���`���v�^�[�i�����j�ɕ\�������`���v�^�[�i���o�[
	Revolution* select_numbers_s_;				// �X�e�[�W�i���o�[��S�T�C�Y
	Revolution* select_numbers_m_left_;			// �X�e�[�W�i���o�[�i���j
	Revolution* select_numbers_m_center_;		// �X�e�[�W�i���o�[�i���j
	Revolution* select_numbers_m_right_;		// �X�e�[�W�i���o�[�i�E�j
	Revolution* select_numbers_w_;				// �X�e�[�W�i���o�[��L�T�C�Y
	int chapter_ = 0;							// ��
	int stage_	 = 0;							// �X�e�[�W
	std::array<std::array<std::function<void()>, STAGE_MAX>, CHAPTER_MAX> select_stages_;	// 5*5���̃X�e�[�W�p�Y�����z��
	// �I�v�V�����{�^������̃I�u�W�F�N�g�ƕϐ�
	std::array<Revolution*, 10> option_images_;	// �I�v�V������ʂ̓������Ȃ������Ȃ���
	Revolution* option_ball_slider_bgm_;		// BGM�{�[���X���C�_�[
	Revolution* option_ball_slider_se_;			// SE�{�[���X���C�_�[
	Revolution* option_stick_slider_bgm_;		// BGM�X�e�B�b�N�X���C�_�[
	Revolution* option_stick_slider_se_;		// SE�X�e�B�b�N�X���C�_�[
	void StageSelect();
	void MoveSelect();
};

#endif  // TITLE_SCENE_H_