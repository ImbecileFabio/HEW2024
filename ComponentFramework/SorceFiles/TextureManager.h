
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

#include <SimpleMath.h>

#include "SubSystem/Texture.h"

using namespace DirectX::SimpleMath;

/*----- 構造体定義 -----*/
struct TextureInfo {
	std::string filePath;	// ファイルパス
	Vector2 offsetPos;
	Vector2 offsetSize;
	bool loop;				// ループフラグ
	int cutU;				// 横分割数
	int cutV;				// 縦分割数	
	float animationSpeed;	// アニメーションスピード
	int totalFrame;			// 総フレーム数
};
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


	// テクスチャの取得
	std::shared_ptr<Texture> GetTexture(const std::string& _imgName);

private:
	// シングルトンなのでprivateに
	TextureManager();
	~TextureManager();

	// テクスチャの情報を保持
	void RegisterTextureInfo(const std::string& _textureName, const TextureInfo& _textureInfo);

	// テクスチャの登録
	void RegisterTexture(const std::string& _imgName, const std::string& _fileName, const DirectX::SimpleMath::Vector2& _offsetPos, const DirectX::SimpleMath::Vector2& _offsetSize, bool _loopFlg = false, int _cutU = 1, int _cutV = 1, float _anmSpeed = 0.1f, int _totalFrame = 1);	// すべて
	void RegisterTexture(const std::string& _imgName, const std::string& _fileName, bool _loopFlg = false, int _cutU = 1, int _cutV = 1, float _anmSpeed = 0.1f, int _totalFrame = 1);// オフセットなし

	// テクスチャの情報登録
	void RegisterAllTextures();
	// 解放処理
	void ClearCache(void);

	// テクスチャ情報
	std::unordered_map<std::string, TextureInfo> texture_info_;
	// テクスチャキャッシュ
	std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache_;

	// LRUキャッシュ管理用
	std::list<std::string> lru_list_;
	std::unordered_map<std::string, std::list<std::string>::iterator> lru_map_;
	size_t max_cache_size_ = 20; // 最大キャッシュサイズ

};


#endif TEXTURE_MANAGER_H_