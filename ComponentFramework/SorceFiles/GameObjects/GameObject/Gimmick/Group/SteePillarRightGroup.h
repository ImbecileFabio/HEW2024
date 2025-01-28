//=================================================================
// [SteePillarRightGroup.h] 脆い床タイルを管理するグループクラス
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：鉄柱の右タイルをまとめて管理するクラス
//=================================================================
#ifndef STEE_PILLAE_RIGHT_GROUP_H_
#define STEE_PILLAE_RIGHT_GROUP_H_
/*----- インクルード -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 鉄柱の右タイルを管理するグループオブジェクト
//--------------------------------------------------
class SteePillarRightGroup : public GameObject
{
public:
	enum class RightState
	{
		Idle,		// 初期状態
		Breaking,	// 劣化アニメ再生中
		Broken,		// 劣化アニメ完了
		Falling,	// 落下状態
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

	void AddSteePillarRightTile(GameObject* _tile);					// グループにタイルを追加
private:
	// グループ単体が管理しているもの
	std::vector<GameObject*> steePillarRightTiles_;			// グループが管理したいタイル

	bool isStart_;			// 一回だけ実行したかどうか
	bool isBreak_;			// 劣化状態になったかどうか
	bool isBreakStop_;		// 劣化状態の停止
	bool isBreakStart_;
	bool isDownStart_;
	bool isAnimationEnd_;	// アニメーションが終わったら
	// キャッシュ
	class AnimationComponent* owner_top_animation_component_;
	class SpriteComponent* owner_top_sprite_component_;
};
#endif // STEE_PILLAE_RIGHT_GROUP_H_

