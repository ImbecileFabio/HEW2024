//==================================================
// [DebugCollisionDrawComponent.h] �����蔻��`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�f�o�b�O�p�̕`��R���|�[�l���g�̐錾
//==================================================
#ifndef DEBUG_COLLISION_DRAW_COMPONENT_H_
#define DEBUG_COLLISION_DRAW_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <string>

#include "../RenderComponent.h"
#include "../../../SubSystem/VertexBuffer.h"
#include "../../../SubSystem/IndexBuffer.h"
#include "../../../SubSystem/Shader.h"


using namespace DirectX::SimpleMath;

/*----- �\���̒�` -----*/
struct GeometryShaderBuffer {
	DirectX::XMFLOAT4X4 viewProjMatrix;	// �r���[�E�v���W�F�N�V�����s��
	float thickness;					// ���̑���	
	float padding[3];					// 16�o�C�g�A���C�����g�p
};

/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------
// �`��N���X
//--------------------------------------------------
class DebugCollisionDrawComponent :
	public RenderComponent
{
public:
	DebugCollisionDrawComponent(GameObject* _owner,int _drawOrder = 90);
	~DebugCollisionDrawComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw();


	//TypeID GetComponentType(void) const override { return TypeID::DebugCollisionDrawComponent; }

private:
	// �����蔻��`��
	void DrawLine(const Vector2& _start, const Vector2& _end, const Color& _color, const float& _tickness);

	ID3D11Buffer* constant_buffer_ = nullptr;	// �萔�o�b�t�@


};
#endif	// DEBUG_COLLISION_DRAW_COMPONENT_H_