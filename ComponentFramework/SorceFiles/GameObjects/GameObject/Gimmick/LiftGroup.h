//=================================================================
// [LiftGroup.h] リフトグループオブジェクト
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：リフトをまとめて管理するクラス
//=================================================================
#ifndef LIFT_GROUP_H_
#define LIFT_GROUP_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// リフトグループオブジェクト
//--------------------------------------------------
class LiftGroup : public GameObject
{
public:
	LiftGroup(GameManager* _gameManager);
	~LiftGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::LiftGroup; }

	void AddLiftTile(GameObject* _tile);					// グループにタイルを追加
	void SetPendulumANDMovement(GameObject* _centerPendulum);	// グループに中心の振り子を設定


	void UpdateLiftTilePositions(); // 仮の関数
private:
	// グループ単体が管理しているもの
	bool isLeftRight_ = false;
	bool isCenterMedian = false;						// 中心値を調べたかどうか
	int tileCenterNum_ = 0;								// タイルの中心の添え字
	int leftIndex_	   = 0;
	int rightIndex_	   = 0;
	int centerIndex_ = 0;
	GameObject* centerPendulum_ = nullptr;				// 中心の振り子
	std::vector<GameObject*> liftTiles_;				// グループが管理したいタイル
	std::vector<DirectX::SimpleMath::Vector3> initialPositions_; // 各リフトタイルの初期位置

	// キャッシュしたコンポーネント
	class PendulumMovementComponent* owner_pendulum_movement_{};	// 振り子の動き
	std::vector<class LiftComponent*>  owner_lift_components_{};	// リフトコンポーネント

};
#endif // LIFT_GROUP_H_
