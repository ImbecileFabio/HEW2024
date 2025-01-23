//==================================================
// [DebugColliderDrawComponent.h] �����蔻��`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�f�o�b�O�p�̕`��R���|�[�l���g�̐錾
//==================================================
#ifndef DEBUG_COLLISION_DRAW_COMPONENT_H_
#define DEBUG_COLLISION_DRAW_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <string>

#include "RenderComponent.h"
#include "../../../SubSystem/Shader.h"


using namespace DirectX::SimpleMath;


/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------
// �`��N���X
//--------------------------------------------------
class DebugColliderDrawComponent :
	public RenderComponent
{
public:
	DebugColliderDrawComponent(GameObject* _owner,int _drawOrder = 100);
	~DebugColliderDrawComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw();

	void InitDebugBuffers();
	//TypeID GetComponentType(void) const override { return TypeID::DebugColliderDrawComponent; }

private:

};
#endif	// DEBUG_COLLISION_DRAW_COMPONENT_H_