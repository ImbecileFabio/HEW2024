#include "Revolution.h"
#include "../Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Revolution::Revolution(GameManager* _gameManager, const std::string _imgName)
	: GameObject(_gameManager, "Revolution")
{
	sprite_component_ = new SpriteComponent(this, _imgName, 0);
	this->InitGameObject();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Revolution::~Revolution()
{
	delete sprite_component_;
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void Revolution::InitGameObject()
{

}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Revolution::UpdateGameObject()
{
}
