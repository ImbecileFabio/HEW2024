//==================================================
// [IndexComponent.h] 
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F
//==================================================


/*----- �C���N���[�h -----*/
#include "../../StdAfx.h"
#include "IndexComponent.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
IndexComponent::IndexComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}


//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
IndexComponent::~IndexComponent(void)
{
}

//=======================================
//����������
//=======================================
void IndexComponent::Init()
{
	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// �C���f�b�N�X�o�b�t�@����
	index_buffer_.Create(indices);

}
