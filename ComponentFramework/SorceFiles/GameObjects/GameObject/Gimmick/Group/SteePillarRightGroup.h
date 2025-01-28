//=================================================================
// [SteePillarRightGroup.h] �Ƃ����^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�S���̉E�^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef STEE_PILLAE_RIGHT_GROUP_H_
#define STEE_PILLAE_RIGHT_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- �O���錾 -----*/
//--------------------------------------------------
// �S���̉E�^�C�����Ǘ�����O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarRightGroup : public GameObject
{
public:
	enum class RightState
	{
		Idle,		// �������
		Breaking,	// �򉻃A�j���Đ���
		Broken,		// �򉻃A�j������
		Falling,	// �������
	};
	SteePillarRightGroup(GameManager* _gameManager);
	~SteePillarRightGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRightGroup; }

	void SetIsBreak	   (bool _fg) { isBreak_ = _fg; }
	void SetIsDownStart(bool _fg) { isDownStart_ = _fg; }
	void SetIsBreakStop(bool _fg) { isBreakStop_ = _fg; }
	bool GetIsAnimationEnd() { return isAnimationEnd_; }
	bool GetIsBreakStop()	 { return isBreakStop_; }

	void AddSteePillarRightTile(GameObject* _tile);					// �O���[�v�Ƀ^�C����ǉ�
private:
	// �O���[�v�P�̂��Ǘ����Ă������
	std::vector<GameObject*> steePillarRightTiles_;			// �O���[�v���Ǘ��������^�C��

	bool isStart_;			// ��񂾂����s�������ǂ���
	bool isBreak_;			// �򉻏�ԂɂȂ������ǂ���
	bool isBreakStop_;		// �򉻏�Ԃ̒�~
	bool isBreakStart_;
	bool isDownStart_;
	bool isAnimationEnd_;	// �A�j���[�V�������I�������
	// �L���b�V��
	class AnimationComponent* owner_top_animation_component_;
	class SpriteComponent* owner_top_sprite_component_;
};
#endif // STEE_PILLAE_RIGHT_GROUP_H_

