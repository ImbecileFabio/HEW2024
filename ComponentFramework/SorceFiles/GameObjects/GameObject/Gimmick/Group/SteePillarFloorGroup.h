//=================================================================
// [SteePillarFloorGroup.h] 脆い床タイルを管理するグループクラス
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：脆い床タイルをまとめて管理するクラス
//=================================================================
#ifndef STEE_PILLAE_FLOOR_GROUP_H_
#define STEE_PILLAE_FLOOR_GROUP_H_
/*----- インクルード -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 脆い床タイルを管理するグループオブジェクト
//--------------------------------------------------
class SteePillarFloorGroup : public GameObject
{
public:
	SteePillarFloorGroup(GameManager* _gameManager);
	~SteePillarFloorGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarFloorGroup; }

	void SetWeakFloorBreak(bool _isBreak) { isWeakFloorBreak_ = _isBreak; }	// 脆い床が壊れたかどうかを設定

	void AddWeakFloorTile(GameObject* _tile);					// グループにタイルを追加
	void SetPendulumANDMovement(GameObject* _centerPendulum);	// グループに中心の振り子を設定
private:
	class TimerComponent* timer_component_;				// タイマーコンポーネント
	// グループ単体が管理しているもの
	bool isWeakFloorBreak_ = false;						// 脆い床が壊れたかどうか
	bool isCenterMedian = false;						// 中心値を調べたかどうか
	int tileCenterNum_ = 0;								// タイルの中心の添え字
	GameObject* centerPendulum_ = nullptr;				// 中心の振り子
	std::vector<GameObject*> weakFloorTiles_;			// グループが管理したいタイル

	// キャッシュしたコンポーネント
	class PendulumMovementComponent* owner_pendulum_movement_{};	// 振り子の動き
};
#endif // STEE_PILLAE_FLOOR_GROUP_H_

