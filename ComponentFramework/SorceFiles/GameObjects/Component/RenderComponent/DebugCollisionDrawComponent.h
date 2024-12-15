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
#include "../../../SubSystem/ConstantBuffer.h"
#include "../../../SubSystem/Shader.h"


using namespace DirectX::SimpleMath;


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


};
#endif	// DEBUG_COLLISION_DRAW_COMPONENT_H_