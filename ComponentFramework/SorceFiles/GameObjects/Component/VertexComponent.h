//==================================================
// [VertexComponent.h] �R���C�_�[�̃x�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�������p�����ē����蔻������
//==================================================
#ifndef VERTEX_COMPONENT_H_
#define VERTEX_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "../Component.h"
#include "../../subSystem/IndexBuffer.h "
#include "../../subSystem/VertexBuffer.h "

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �R���C�_�[�R���|�[�l���g
//--------------------------------------------------
class VertexComponent :
    public Component
{
public:
    VertexComponent(class GameObject* owner, int updateOrder = 100);
    ~VertexComponent(void);

    void Init();

    virtual TypeID GetComponentType() const override { return TypeID::VertexComponent; }

private:
    IndexBuffer	 index_buffer_; // �C���f�b�N�X�o�b�t�@
    VertexBuffer<VERTEX_3D>	vertex_buffer_; // ���_�o�b�t�@

};



#endif	// COLLIDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
