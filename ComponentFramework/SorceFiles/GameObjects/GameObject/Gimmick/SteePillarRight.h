//=================================================================
// [SteePillarRight.h] �S���̃I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���̃I�u�W�F�N�g�̐錾
//=================================================================
#ifndef STEE_PILLAR_H_
#define STEE_PILLAR_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
// SteePillarRight�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarRight : public GameObject
{
public:
	SteePillarRight(GameManager* _gameManager);
	~SteePillarRight(void);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRight; }

	void SetPillarRightGroup(class SteePillarRightGroup* _group);

	void SetIsDown(bool _fg) { isDown_ = _fg; }
	bool GetIsDown() { return isDown_; }
	void SetIsFloorVelocityStop(bool _fg) { isFloorVelocityStop_ = _fg; }
	bool GetIsFloorVelocityStop() { return isFloorVelocityStop_; }

	void SetFloorPosition(DirectX::SimpleMath::Vector3 _pos) { floorPosition_ = _pos; }
private:
	class SteePillarRightGroup* stee_pillar_right_group_;
	class SpriteComponent*			   sprite_component_;
	class AnimationComponent*		animation_component_;
	class VelocityComponent*		 velocity_component_;
	class GravityComponent*			  gravity_component_;

	DirectX::SimpleMath::Vector3 floorPosition_;
	DirectX::SimpleMath::Vector3 offset_;

	bool isFloorVelocityStop_ = false;
	bool isDown_   = false;
};
#endif // STEE_PILLAR_H_
