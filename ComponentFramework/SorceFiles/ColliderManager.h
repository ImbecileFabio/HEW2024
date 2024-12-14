//=================================================================
// [ColiderManager.h] コライダーマネージャーモジュールヘッダ
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：コライダーの管理を行うクラス
//=================================================================
#ifndef COLLDIER_MANAGER_H_
#define COLLIDER_MANAGER_H_
/*----- インクルード -----*/
#include<memory>
#include<vector>
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
//-----------------------------------------------------------------
// コライダーマネージャークラス
//-----------------------------------------------------------------
class ColliderManager
{
public:
	ColliderManager(void);
	~ColliderManager(void);
	// インスタンス生成
	static auto Create(void) { return new ColliderManager(); }
	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
	// ゲームオブジェクトの追加
	void AddGameObject(GameObject* _gameObject);
	// ゲームオブジェクトの削除
	void RemoveGameObject(GameObject* _gameObject);
private:
	//更新処理
	void UpdateGameObjects(void);
	// オブジェクトが更新中か確認
	bool updating_game_objects_;
	std::vector<GameObject*> collider_game_objects_{};	// 当たり判定用コンテナ
	std::vector<GameObject*> collider_out_objects_{};	// 当たり判定を取らないコンテナ
	std::vector<GameObject*> pending_game_objects_{};	// 待機コンテナ
};
#endif // _COLLDIER_MANAGER_H_