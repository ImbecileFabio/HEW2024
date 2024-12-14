////==================================================
//// [DebugPolygonComponent.h] �|���S���`��R���|�[�l���g
//// ���ҁF����仓�
////--------------------------------------------------
//// �����FPolygon�`��
////==================================================
//#include "DebugPolygonComponent.h"
//#include "../../../GameManager.h"
//using namespace DirectX::SimpleMath;
////--------------------------------------------------
//// �R���X�g���N�^
////--------------------------------------------------
//DebugPolygonComponent::DebugPolygonComponent(GameObject* _owner, int _drawOrder)
//	:RenderComponent(_owner, _drawOrder)
//{
//	// �o�b�t�@������
//	InitBuffers();
//
//	// �`��I�u�W�F�N�g�Ƃ��ēo�^
//	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);
//}
////--------------------------------------------------
//// �f�X�g���N�^
////--------------------------------------------------
//DebugPolygonComponent::~DebugPolygonComponent()
//{
//}
////--------------------------------------------------
//// �|���S���\���̏���������
////--------------------------------------------------
//void DebugPolygonComponent::Init(void)
//{
//}
////--------------------------------------------------
//// �|���S���\���̏I������
////--------------------------------------------------
//void DebugPolygonComponent::Uninit(void)
//{
//}
////--------------------------------------------------
//// �|���S���\���̍X�V����
////--------------------------------------------------
//void DebugPolygonComponent::Update(void)
//{
//}
//
//void DebugPolygonComponent::InitBuffers()
//{
//	// ���_�f�[�^
//	std::vector<VERTEX_3D>	vertices;
//
//	vertices.resize(4);
//
//	vertices[0].position = Vector3(-0.5f, 0.5f, 0.5f);
//	vertices[1].position = Vector3(0.5f, 0.5f, 0.5f);
//	vertices[2].position = Vector3(-0.5f, -0.5f, 0.5f);
//	vertices[3].position = Vector3(0.5f, -0.5f, 0.5f);
//
//	vertices[0].color = Color(1, 1, 1, 1);
//	vertices[1].color = Color(1, 1, 1, 1);
//	vertices[2].color = Color(1, 1, 1, 1);
//	vertices[3].color = Color(1, 1, 1, 1);
//
//	vertices[0].uv = Vector2(0, 0);
//	vertices[1].uv = Vector2(1, 0);
//	vertices[2].uv = Vector2(0, 1);
//	vertices[3].uv = Vector2(1, 1);
//
//	// ���_�o�b�t�@����
//	vertex_buffer_.Create(vertices);
//
//	// �C���f�b�N�X�o�b�t�@����
//	std::vector<unsigned int> indices;
//	indices.resize(4);
//
//	indices[0] = 0;
//	indices[1] = 1;
//	indices[2] = 2;
//	indices[3] = 3;
//
//	// �C���f�b�N�X�o�b�t�@����
//	index_buffer_.Create(indices);
//
//	// �V�F�[�_�I�u�W�F�N�g����
//	shader_.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
//}
//
