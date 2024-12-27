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

	static std::string SerializeGameObject  (const GameObject* _gameObject);
	static GameObject* DeserializeGameObject(const std::string& _data);

	// その他のコンポーネントも同様にシリアライズ/デシリアライズ用の関数を追加
	static std::string SerializeComponent  (const Component* _component);
	static Component*  DeserializeComponent(const std::string& _data);
private:
	SerializeManager();	 //コンストラクタ
	~SerializeManager(); //デストラクタ
};

#endif // SERIALIZE_MANAGER_H_

