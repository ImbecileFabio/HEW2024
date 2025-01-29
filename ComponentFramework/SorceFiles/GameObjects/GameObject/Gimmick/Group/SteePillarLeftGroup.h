//=================================================================
// [SteePillarLeftGroup.h] ���S���̃^�C�����Ǘ�����O���[�v�N���X
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F���S���^�C�����܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef STEE_PILLAE_LEFT_GROUP_H_
#define STEE_PILLAE_LEFT_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- �O���錾 -----*/
//--------------------------------------------------
// ���S���^�C�����Ǘ�����O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarLeftGroup : public GameObject
{
public:
	SteePillarLeftGroup(GameManager* _gameManager);
	~SteePillarLeftGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarLeftGroup; }

	void SetIsBreak	   (bool _fg) { isBreak_ = _fg; }
	void SetIsBreakStop(bool _fg) { isBreakStop_ = _fg; }
	void SetIsDownStart(bool _fg) { isDownStart_ = _fg; }
	bool GetIsAnimationEnd() { return isAnimationEnd_; }
	bool GetIsBreakStop() { return isBreakStop_; }
	void SetVelocityStop();
	void AddSteePillarLeftTile(GameObject* _tile);	// �O���[�v�Ƀ^�C����ǉ�
private:
	// �O���[�v�P�̂��Ǘ����Ă������
	std::vector<GameObject*> steePillarLeftTiles_;	// �O���[�v���Ǘ��������^�C��

	bool isStart_;			// ��񂾂����s�������ǂ���
	bool isBreakStop_;		// �򉻂��~
	bool isBreak_;			// �򉻏�ԂɂȂ������ǂ���
	bool isBreakStart_;		// �򉻏�ԁi�n���j
	bool isDownStart_;		// ����	   �i�n���j
	bool isAnimationEnd_;	// �A�j���[�V�������I�������
	// ���̈�ԏ�̃^�C�����L���b�V��
	class AnimationComponent* owner_top_animation_component_;
	class SpriteComponent*	  owner_top_sprite_component_;
};
#endif // STEE_PILLAE_LEFT_GROUP_H_

