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

	void SetHitTile(bool _fg) { isHitTile_ = _fg; }

	TypeID GetType(void) override { return TypeID::SteePillarFloorGroup; }

	void AddSteePillarFloorTile(GameObject* _tile);					// グループにタイルを追加
	void SetPendulumANDMovement(GameObject* _centerPendulum);		// グループに中心の振り子を設定

	void SetSteePillarLeftGroup(class SteePillarLeftGroup* _steePillarLeftGroup);		// 左側のグループを設定
	void SetSteePillarRightGroup(class SteePillarRightGroup* _steePillarRightGroup);	// 右側のグループを設定
	void SetHitLeft(bool _fg) { isHitLift_ = _fg; }
	void UpdateSteePillarFloorTilePositions();	// タイルの位置を同期させる関数
	void AlignSteePillarFloorTilesWithTile(float _y);
	bool GetIsHitLift_() { return isHitLift_; }
private:
	// グループ単体が管理しているもの
	bool isCenterMedian_ = false;						// 中心値を調べたかどうか
	bool isOddNumber_	 = false;						// 偶数か奇数かどうか
	bool isBreakStart_	 = false;
	bool isDownStart_	 = false;						
	bool isHitTile_		 = false;						// タイルが当たったかどうか
	bool isHitLift_		 = false;						// リフトが当たったかどうか
	bool isPendulumDelete_ = false;						// 振り子を消すかどうか
	int tileCenterNum_ = 0;								// タイルの中心の添え字
	int leftIndex_ = 0;
	int rightIndex_ = 0;

	GameObject* centerPendulum_ = nullptr;				// 中心の振り子
	std::vector<GameObject*> steePillarFloorTiles_;		// グループが管理したいタイル

	std::vector<DirectX::SimpleMath::Vector3> initialPositions_; // 各鉄柱床の初期位置

	// キャッシュしたコンポーネント
	class PendulumMovementComponent* owner_pendulum_movement_{};	// 振り子の動き

	// グループが管理しているもの
	class SteePillarLeftGroup*  steePillarLeftGroup_  = nullptr;		// 左側のグループ
	class SteePillarRightGroup* steePillarRightGroup_ = nullptr;		// 右側のグループ

	void CacheInitPosition();	// 初期位置をキャッシュする関数
	void UpdatePendulumState();	// 振り子の状態を更新する関数
	void StartFalling();		// 落下処理を開始する関数	
	DirectX::SimpleMath::Vector3 GetCenterPosition();	// タイルの中心位置を取得する関数
};
#endif // STEE_PILLAE_FLOOR_GROUP_H_

