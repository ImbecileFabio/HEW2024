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

//==================================================
// �X�e�[�W1-1�V�[���N���X
//==================================================
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
	// ������I�u�W�F�N�g�������ɋL�q

	class Player* player_{};		// �v���C���[
	class Camera* camera_{};		// �J����
	class Pendulum* pendulum_{};	// �U��q
	class Tile* tile_{};			// �^�C��
	class TestObject* test_object_{};
	class Robot* robot_{};

};

#endif  // STAGE1_1SCENE_H_