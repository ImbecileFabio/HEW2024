//=================================================================
// [SteePillarLeftGroup.h] 左鉄柱のタイルを管理するグループクラス
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：左鉄柱タイルをまとめて管理するクラス
//=================================================================
#ifndef STEE_PILLAE_LEFT_GROUP_H_
#define STEE_PILLAE_LEFT_GROUP_H_
/*----- インクルード -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 左鉄柱タイルを管理するグループオブジェクト
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
	void AddSteePillarLeftTile(GameObject* _tile);	// グループにタイルを追加
private:
	// グループ単体が管理しているもの
	std::vector<GameObject*> steePillarLeftTiles_;	// グループが管理したいタイル

	bool isStart_;			// 一回だけ実行したかどうか
	bool isBreakStop_;		// 劣化を停止
	bool isBreak_;			// 劣化状態になったかどうか
	bool isBreakStart_;		// 劣化状態（始動）
	bool isDownStart_;		// 落下	   （始動）
	bool isAnimationEnd_;	// アニメーションが終わったら
	// 柱の一番上のタイルをキャッシュ
	class AnimationComponent* owner_top_animation_component_;
	class SpriteComponent*	  owner_top_sprite_component_;
};
#endif // STEE_PILLAE_LEFT_GROUP_H_

