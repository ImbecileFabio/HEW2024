//==================================================
// [Stage3_2Scene.h] �X�e�[�W1-4�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W3-2���Ǘ�������N���X
//==================================================
#ifndef STAGE3_2SCENE_H_
#define STAGE3_2SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// �X�e�[�W3-2�V�[���N���X
//--------------------------------------------------
class Stage3_2Scene : public SceneBase
{
public:
	Stage3_2Scene(GameManager* _gameManager);
	~Stage3_2Scene();

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

#endif // STAGE3_2SCENE_H_