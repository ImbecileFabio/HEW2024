//=================================================================
// [SteePillarRightGroup.h] 脆い床タイルを管理するグループクラス
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：脆い床タイルをまとめて管理するクラス
//=================================================================
#ifndef STEE_PILLAE_RIGHT_GROUP_H_
#define STEE_PILLAE_RIGHT_GROUP_H_
/*----- インクルード -----*/
#include "../../../GameObject.h"
#include <vector>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 脆い床タイルを管理するグループオブジェクト
//--------------------------------------------------
class SteePillarRightGroup : public GameObject
{
public:
	SteePillarRightGroup(GameManager* _gameManager);
	~SteePillarRightGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRightGroup; }

	void AddSteePillarRightTile(GameObject* _tile);					// グループにタイルを追加
private:
	class TimerComponent* timer_component_;					// タイマーコンポーネント
	// グループ単体が管理しているもの
	std::vector<GameObject*> steePillarRightTiles_;			// グループが管理したいタイル
};
#endif // STEE_PILLAE_RIGHT_GROUP_H_

