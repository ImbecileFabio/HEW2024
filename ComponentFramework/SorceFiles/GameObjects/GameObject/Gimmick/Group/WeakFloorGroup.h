//=================================================================
// [WeakFloorGroup.h] 脆い床タイルを管理するグループクラス
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：脆い床タイルをまとめて管理するクラス
//=================================================================
#ifndef WEAK_FLOOR_GROUP_H_
#define WEAK_FLOOR_GROUP_H_
/*----- インクルード -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 脆い床タイルを管理するグループオブジェクト
//--------------------------------------------------
class WeakFloorGroup : public GameObject
{
public:
	WeakFloorGroup(GameManager* _gameManager);
	~WeakFloorGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::WeakFloorGroup; }

	void SetWeakFloorBreak(bool _isBreak) { isWeakFloorBreak_ = _isBreak; }	// 脆い床が壊れたかどうかを設定

	void AddWeakFloorTile (GameObject* _tile);					// グループにタイルを追加
	void SetPendulumANDMovement(GameObject* _centerPendulum);	// グループに中心の振り子を設定

	int GetHitCount() { return hitCount_; }

	void SetPendulumOn(bool _fg) { isPendulumOn_ = _fg; }
private:
	int hitCount_ = 0;
	class TimerComponent* timer_component_;				// タイマーコンポーネント
	// グループ単体が管理しているもの
	bool isWeakFloorBreak_		 = false;				// 脆い床が壊れたかどうか
	bool isCenterMedian			 = false;				// 中心値を調べたかどうか
	bool isPendulumOn_			 = false;				// 振り子あるかないか
	int tileCenterNum_			 = 0;					// タイルの中心の添え字
	GameObject* centerPendulum_ = nullptr;				// 中心の振り子
	std::vector<GameObject*> weakFloorTiles_;			// グループが管理したいタイル

	// キャッシュしたコンポーネント
	class PendulumMovementComponent* owner_pendulum_movement_{};	// 振り子の動き
};
#endif // WEAK_FLOOR_GROUP_H_

