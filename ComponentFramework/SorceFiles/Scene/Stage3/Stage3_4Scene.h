//==================================================
// [Stage3_4Scene.h] �X�e�[�W3-4�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W3-4���Ǘ�������N���X
//==================================================
#ifndef STAGE3_4SCENE_H_
#define STAGE3_4SCENE_H_
/*----- �C���N���[�h -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// �X�e�[�W3-4�V�[���N���X
//--------------------------------------------------
class Stage3_4Scene : public SceneBase
{
public:
	Stage3_4Scene(GameManager* _gameManager);
	~Stage3_4Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;

	enum STATE {
		Game,
		Result,
		Pouse,
		Rewind
	};
private:
	STATE state_;

	// ������I�u�W�F�N�g�������ɋL�q
	class BackGround* back_ground_{};			// �w�i
	class Camera* camera_{};					// �J����
	class HammerCursor* hammerCursor_{};		// �n���}�[�J�[�\��
	std::vector<class Item*> items_;			// �A�C�e�����X�g
	std::array<class Revolution*, 2> stageUIs_;	// �����̂Ȃ��X�e�[�WUI
};

#endif // STAGE3_4SCENE_H_