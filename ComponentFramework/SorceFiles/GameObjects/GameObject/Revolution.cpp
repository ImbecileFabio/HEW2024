#include "Revolution.h"
#include "../Component/RenderComponent/SpriteComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Revolution::Revolution(GameManager* _gameManager, const std::string _imgName)
	: GameObject(_gameManager, "Revolution")
{
	sprite_component_ = new SpriteComponent(this, _imgName, 0);
	sound_.Init();
	sound_.Play(SoundLabel_TitleBGM);
	this->InitGameObject();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Revolution::~Revolution()
{
	delete sprite_component_;
	sound_.Stop(SoundLabel_TitleBGM);
	sound_.Uninit();
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
