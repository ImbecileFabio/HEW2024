//==================================================
// [SerializeManager.h] シリアライズを管理するクラスのヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：シリアライズ・デシリアライズを管理するクラス
//==================================================
#ifndef SERIALIZE_MANAGER_H_
#define SERIALIZE_MANAGER_H_
/*----- インクルード -----*/
#include <string>
/*----- 前方宣言 -----*/
class GameObject;
class Component;
//-----------------------------------------------------------------
// シリアライズ管理マネージャークラス
//-----------------------------------------------------------------
class SerializeManager
{
public:
	// シングルトンなるものをコピペ
	static SerializeManager& GetInstance()
	{
		static SerializeManager instance;
		return instance;
	}
	SerializeManager(const SerializeManager&) = delete;
	SerializeManager& operator=(const SerializeManager&) = delete;

	static std::string SerializeGameObject(const GameObject* _gameObject);	// ゲームオブジェクトをシリアライズする関数
	static GameObject* DeserializeGameObject(const std::string& _data);

	static std::string SerializeComponent(const Component* _component);	// コンポーネントをシリアライズする関数
	static Component*  DeserializeComponent(const std::string& _data);
private:
	SerializeManager();	 //コンストラクタ
	~SerializeManager(); //デストラクタ
};

#endif // SERIALIZE_MANAGER_H_

