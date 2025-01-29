//==================================================
// [Stage1_2Scene.h] �X�e�[�W1-2�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-2���Ǘ�������N���X
//==================================================
#ifndef STAGE1_2SCENE_H_
#define STAGE1_2SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"

#include <array>
//--------------------------------------------------
// �X�e�[�W1-2�V�[���N���X
//--------------------------------------------------
class Stage1_2Scene :  public SceneBase
{
public:
	Stage1_2Scene(GameManager* _gameManager);
	~Stage1_2Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;


private:
	// ������I�u�W�F�N�g�������ɋL�q
	class BackGround* back_ground_{};			// �w�i
	class Camera* camera_{};					// �J����
	class HammerCursor* hammerCursor_{};		// �n���}�[�J�[�\��
	std::vector<class Item*> items_;			// �A�C�e�����X�g
	std::array<class Revolution*, 2> stageUIs_;	// �����̂Ȃ��X�e�[�WUI
};

#endif // STAGE1_2SCENE_H_