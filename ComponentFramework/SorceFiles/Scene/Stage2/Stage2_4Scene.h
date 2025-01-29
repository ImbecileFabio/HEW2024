//==================================================
// [Stage2_4Scene.h] �X�e�[�W1-4�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W2-4���Ǘ�������N���X
//==================================================
#ifndef STAGE2_4SCENE_H_
#define STAGE2_4SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// �X�e�[�W2-4�V�[���N���X
//--------------------------------------------------
class Stage2_4Scene : public SceneBase
{
public:
	Stage2_4Scene(GameManager* _gameManager);
	~Stage2_4Scene();

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

#endif // STAGE2_4SCENE_H_