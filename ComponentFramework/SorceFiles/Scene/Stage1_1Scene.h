//==================================================
// [Stage1_1Scene.h] �X�e�[�W1-1�V�[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�X�e�[�W1-1���Ǘ�������N���X
//==================================================
#ifndef STAGE1_1SCENE_H_
#define STAGE1_1SCENE_H_

/*----- �C���N���[�h -----*/
#include "SceneBase.h"

//--------------------------------------------------
// �X�e�[�W1-1�V�[���N���X
//--------------------------------------------------
class Stage1_1Scene :
	public SceneBase
{
public:
	Stage1_1Scene(GameManager* _gameManager);
	~Stage1_1Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;


private:
	// �Q�[���̏��
	enum STATE {
		Game,
		Result,
		Pouse,
		Rewind
	};
	STATE State;

	// ������I�u�W�F�N�g�������ɋL�q
	class BackGround* back_ground_{};	// �w�i
	class Camera* camera_{};			// �J����
	class Pendulum* pendulum_{};		// �U��q
	class Pendulum* pendulum_2_{};
	class Pendulum* pendulum_3_{};
	class Tile* tile_{};				// �^�C��
	class Robot* robot_{};				// ���{�b�g
	class Lift*	 lift_{};				// ���t�g
	std::vector<class Item*> items_;	// �A�C�e�����X�g
};
#endif  // STAGE1_1SCENE_H_