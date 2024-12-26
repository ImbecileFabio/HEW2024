//==================================================
// [RenderComponent.h] �`�惂�W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�I�u�W�F�N�g�̕`�������@�\�̐錾
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <memory>

#include "../Component.h"
#include "../../SubSystem/VertexBuffer.h"
#include "../../SubSystem/IndexBuffer.h"
#include "../../SubSystem/Shader.h"
#include "../../SubSystem/Material.h"


/*----- �\���̐錾 -----*/

/*----- �O���錾 -----*/
class GameObject;

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �`��R���|�[�l���g�̃x�[�X�N���X
//--------------------------------------------------
class RenderComponent : public Component
{
public:
	enum class State
	{
		none = -1,
		draw,
		notDraw,
	};
	RenderComponent(GameObject* _owner, int _drawOrder = 50);
	~RenderComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};
	
	virtual void Draw(void) = 0;

	// �X�V���ʂ�Ԃ�
	int& GetDrawOrder(void) { return draw_order_; }


	virtual TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

	// UV���W�̕ύX
	void SetUV(const DirectX::SimpleMath::Vector2& _uv);

	void SetState(State _state) { state_ = _state; }
	State GetState() { return state_; }
protected:
	int draw_order_;	// �X�V����

	void InitBuffers();	// �o�b�t�@�̏�����

	// �o�b�t�@
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;


	Shader shader_;	// �V�F�[�_
	std::unique_ptr<Material> material_;

	std::vector<VERTEX_3D> vertices_;	// ���_�f�[�^

	State state_ = State::draw;	// �`�悷�邩���Ȃ���
};

#endif	// RENDER_COMPONENT_H_