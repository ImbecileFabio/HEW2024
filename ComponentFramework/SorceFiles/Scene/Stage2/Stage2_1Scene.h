//==================================================
// [Stage2_1Scene.h] �X�e�[�W1-4�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-4���Ǘ�������N���X
//==================================================
#ifndef STAGE2_1SCENE_H_
#define STAGE2_1SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// �X�e�[�W1-4�V�[���N���X
//--------------------------------------------------
class Stage2_1Scene : public SceneBase
{
public:
	Stage2_1Scene(GameManager* _gameManager);
	~Stage2_1Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;

private:

	// ������I�u�W�F�N�g�������ɋL�q
	class BackGround* back_ground_{};			// �w�i
	class Camera* camera_{};					// �J����
	class HammerCursor* hammerCursor_{};		// �n���}�[�J�[�\��
	std::vector<class Item*> items_;			// �A�C�e�����X�g
};

#endif // STAGE1_4SCENE_H_