////==================================================
//// [DebugPolygonComponent.h] �f�o�b�O�p�|���S���`��w�b�_�t�@�C��
//// ���ҁF����仓�
////--------------------------------------------------
//// �����F�f�o�b�O�p�|���S���`��̃R���|�[�l���g
////==================================================
//#ifndef DEBUG_POLYGON_COMPONENT_H_
//#define DEBUG_POLYGON_COMPONENT_H_
///*----- �C���N���[�h -----*/
//#include "../RenderComponent.h"
//#include "../../../SubSystem/VertexBuffer.h"
//#include "../../../SubSystem/IndexBuffer.h"
//#include "../../../SubSystem/Shader.h"
//#include "../../../SubSystem/Texture.h"
////--------------------------------------------------
//// �f�o�b�O�p�|���S���`��N���X
////--------------------------------------------------
//class DebugPolygonComponent :public RenderComponent
//{
//public:
//	DebugPolygonComponent(GameObject* _owner, int _drawOrder = 0);
//	~DebugPolygonComponent();
//
//	void Init(void) override;
//	void Uninit(void) override;
//	void Update(void) override;
//
//	TypeID GetComponentType(void) const override { return TypeID::DebugPolygonComponent; }
//
//private:
//	void InitBuffers();	// �o�b�t�@�̏�����
//	// �o�b�t�@
//	VertexBuffer<VERTEX_3D> vertex_buffer_;
//	IndexBuffer index_buffer_;
//
//	Shader shader_;	// �V�F�[�_
//};
//#endif // DEBUG_POLYGON_COMPONENT_H_