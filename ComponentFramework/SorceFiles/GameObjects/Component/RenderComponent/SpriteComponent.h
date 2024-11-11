//==================================================
// [SpriteComponent.h] �`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`��R���|�[�l���g�̐錾
//==================================================
#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "../RenderComponent.h"
#include "../../../SubSystem/VertexBuffer.h"
#include "../../../SubSystem/IndexBuffer.h"
#include "../../../SubSystem/Shader.h"
#include "../../../SubSystem/Texture.h"



/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------
// �`��N���X
//--------------------------------------------------
class SpriteComponent :
    public RenderComponent
{
public:
    SpriteComponent(class GameObject* _owner, const std::string _imgname = NULL, int _drawOrder = 100);
    ~SpriteComponent();

    void Init() override;
    void Update() override;
    void Uninit() override;
    void Draw() ;

    void SetObjectName(std::string _objectName);

    // �X�V���ʂ�Ԃ�
    int& GetDrawOrder(void) { return draw_order_; }
    // �R���|�[�l���g��ID��Ԃ�
    TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

private:
    void InitBuffers();

    int draw_order_;            // �X�V����
    std::string object_name_;   // �I�u�W�F�N�g��

    // �o�b�t�@
    VertexBuffer<VERTEX_3D> vertex_buffer_;
    IndexBuffer index_buffer_;

    // �V�F�[�_
    Shader shader_;

    // �e�N�X�`��
    Texture texture_;
};


#endif	// SPRITE_COMPONENT_H_