//==================================================
// [IndexComponent.h] 
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F
//==================================================
#ifndef INDEX_COMPONENT_H_
#define INDEX_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "../Component.h"
#include "../../subSystem/IndexBuffer.h "

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �R���C�_�[�R���|�[�l���g
//--------------------------------------------------
class IndexComponent :
    public Component
{
public:
    IndexComponent(class GameObject* owner, int updateOrder = 100);
    ~IndexComponent(void);

    void Init();

    virtual TypeID GetComponentType() const override { return TypeID::IndexComponent; }

private:
    IndexBuffer	 index_buffer_; // �C���f�b�N�X�o�b�t�@

};



#endif	// COLLIDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
