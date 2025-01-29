//==================================================
// [Stage3_3Scene.h] �X�e�[�W1-4�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W3-3���Ǘ�������N���X
//==================================================
#ifndef STAGE3_3SCENE_H_
#define STAGE3_3SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// �X�e�[�W3-3�V�[���N���X
//--------------------------------------------------
class Stage3_3Scene : public SceneBase
{
public:
	Stage3_3Scene(GameManager* _gameManager);
	~Stage3_3Scene();

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

#endif // STAGE3_1SCENE_H_