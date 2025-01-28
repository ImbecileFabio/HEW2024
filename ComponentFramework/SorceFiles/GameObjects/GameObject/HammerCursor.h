//=================================================================
// [HammerCursor.h] �U��q��I������J�[�\���w�b�_
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�U��q��I������J�[�\���I�u�W�F�N�g
//=================================================================
#ifndef HAMMER_CURSOR_H_
#define HAMMER_CURSOR_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// �n���}�[�J�[�\���I�u�W�F�N�g
//--------------------------------------------------
class HammerCursor : public GameObject
{
public:
	HammerCursor(GameManager* _gameManager);
	~HammerCursor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::HammerCursor; }
	void HammerCursorMove();
	void SetIsUiDraw(bool _isUiDraw) { isUiDraw_ = _isUiDraw; }
	void SetOriginPos(DirectX::SimpleMath::Vector3 _pos) { origin_pos_ = _pos; }
	void SetDirection(int _direction) { direction_ = _direction; }
private:
	class SpriteComponent* sprite_component_;
	class SpriteComponent* hit_effect_component_;
	class AnimationComponent* animation_component_;
	
	// �L���b�V��
	DirectX::SimpleMath::Vector3 origin_pos_;	// �J�[�\���̊�ƂȂ���W��ۑ�
	DirectX::SimpleMath::Vector3 offset_;		// �J�[�\���̃I�t�Z�b�g	
	bool isUiDraw_ = false;						// UI�̕\�����
	int direction_;		
	};
#endif // HAMMER_CURSOR_H_
