//=================================================================
// [HammerCursor.h] 振り子を選択するカーソルヘッダ
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：振り子を選択するカーソルオブジェクト
//=================================================================
#ifndef HAMMER_CURSOR_H_
#define HAMMER_CURSOR_H_
/*----- インクルード -----*/
#include "../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEオブジェクト
//--------------------------------------------------
class HammerCursor : public GameObject
{
public:
	HammerCursor(GameManager* _gameManager);
	~HammerCursor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::HammerCursor; }

	void SetIsUiDraw(bool _isUiDraw) { isUiDraw = _isUiDraw; }
	void SetOriginPos(DirectX::SimpleMath::Vector3 _pos) { origin_pos_ = _pos; }
private:
	class SpriteComponent* sprite_component_;
	class SpriteComponent* hit_effect_component_;
	class AnimationComponent* animation_component_;
	DirectX::SimpleMath::Vector3 origin_pos_;	// カーソルの基準となる座標を保存
	bool isUiDraw = false;		// UIの表示状態
};
#endif // HOGE_H_
