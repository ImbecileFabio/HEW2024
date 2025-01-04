
//=================================================================
// [TextureManager.h] テクスチャ管理クラス
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：テクスチャのリソース管理を行うクラス
//		 シングルトンでの実装です
//=================================================================
#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#define TEXTURE_PATH "Asset/Texture/"
#define SCENE_PATH	 "Asset/Texture/scene/"
#define UI_PATH		 "Asset/Texture/scene/stageUI/"
#define BACKDROP_PATH "Asset/Texture/backdrop/"

#define TILE_PATH	 "Asset/Texture/tile/"
#define ROBOT_PATH	 "Asset/Texture/robot/"
#define GIMMICK_PATH "Asset/Texture/gimmick/"


/*----- インクルード -----*/
#include <unordered_map>
#include <string>
#include <wrl/client.h>
#include <d3d11.h>
#include <memory>

#include "SubSystem/Texture.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/



//-----------------------------------------------------------------
// テクスチャマネージャ 
//-----------------------------------------------------------------
class TextureManager
{
public:
	// インスタンス取得
	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}

	void Init();
	void Uninit();

	// テクスチャの登録
	bool RegisterTexture(const std::string& _imgName, const std::string& _fileName);
	// テクスチャの取得
	std::shared_ptr<Texture> GetTexture(const std::string& _imgName);


private:
	// シングルトンなのでprivateに
	TextureManager();
	~TextureManager();

	// テクスチャの全登録
	void RegisterAllTextures();
	// 解放処理
	void ClearCache(void);

	// テクスチャキャッシュ
	std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache_;

};


#endif TEXTURE_MANAGER_H_