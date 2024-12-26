//==================================================
// [Revolution.cpp] �摜��`�悷�邽�߂̃I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�摜��`�悷�邽�߂̃I�u�W�F�N�g
//==================================================
#ifndef REVOLUTION_H_
#define REVOLUTION_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"
//--------------------------------------------------
// �摜��`�悷�邽�߂̃I�u�W�F�N�g�N���X
//--------------------------------------------------
class Revolution :
    public GameObject
{
public:
	Revolution(GameManager* _gameManager, const std::string _imgName);
	~Revolution();

	void InitGameObject  () override;
	void UpdateGameObject() override;
private:
	class RenderComponent* sprite_component_{}; // �`��R���|�[�l���g
};

#endif  // REVOLUTION_H_