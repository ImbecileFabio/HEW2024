//==================================================
// [PemdulumManager.cpp] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̊Ǘ��i�I���j
//==================================================

#include "PemdulumManager.h"

//--------------------------------------------------
// �R���X�g���N�^�E�f�X�g���N�^
//--------------------------------------------------
PemdulumManager::PemdulumManager(){
	Init();
}
PemdulumManager::~PemdulumManager(){
	Uninit();
}

//--------------------------------------------------
// �����������E�I�������E�X�V����
//--------------------------------------------------
void PemdulumManager::Init(){
}
void PemdulumManager::Uninit(){
}
void PemdulumManager::Update(){
	// if(�X�e�B�b�N�̓���){
	//	pSelectedObject = ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ��֐�
	// }
}


//--------------------------------------------------
// �U��q���I�u�W�F�N�g�ɒǉ�
//--------------------------------------------------
void PemdulumManager::AddGameObject(GameObject* _object){
	objectList_.push_back(_object);
}

//--------------------------------------------------
// ���ς����ȓ����ł��߂��I�u�W�F�N�g�̃|�C���^��Ԃ�
//--------------------------------------------------
GameObject* PemdulumManager::PemgulumSelect(float _inputStick) {

}