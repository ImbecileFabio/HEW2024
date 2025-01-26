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

	void AddSteePillarLeftTile(GameObject* _tile);					// グループにタイルを追加
private:
	class TimerComponent* timer_component_;				// タイマーコンポーネント
	// グループ単体が管理しているもの
	std::vector<GameObject*> steePillarLeftTiles_;			// グループが管理したいタイル
};
#endif // STEE_PILLAE_LEFT_GROUP_H_

