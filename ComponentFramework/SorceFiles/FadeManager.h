//=================================================================
// [FadeManager.h] フェードマネージャ
// 著者：
//-----------------------------------------------------------------
// 説明：画面をフェードイン、アウトするクラス
//=================================================================
#ifndef FADE_MANAGER_H_
#define FADE_MANAGER_H_

/*----- インクルード -----*/
#include <wrl/client.h>
#include <functional>
#include <string>
#include <memory>

#include <SimpleMath.h>

#include "TextureManager.h"

#include "SubSystem/Shader.h"
#include "SubSystem/VertexBuffer.h"
#include "SubSystem/IndexBuffer.h"
#include "SubSystem/Texture.h"

using namespace DirectX::SimpleMath;

/*----- 列挙型 -----*/
enum class FadeType
{
	In,
	Out
};

/*----- 構造体定義 -----*/


/*----- 前方宣言 -----*/
class GameManager;
//-----------------------------------------------------------------
// フェードマネージャクラス
//-----------------------------------------------------------------
class FadeManager {
public:
	FadeManager(GameManager* _gameManager);
	~FadeManager();

	

	// フェードアウト開始
	void StartFadeOut(const std::string& _fadeOutTex, std::function<void()> on_complete = nullptr);
	// フェードイン開始
	void StartFadeIn(const std::string& _fadeInTex, std::function<void()> on_complete = nullptr);

	void Update(float delta_time);
	void Draw();

	void UpdateUV();

	bool GetIsPlaying() const { return is_playing_; } // フェード中かどうか

	void SetTexture(const std::string& _textureName) { fade_texture_ = TextureManager::GetInstance().GetTexture(_textureName); }

private:
	void InitBuffers(float _cutU = 1, float _cutV = 1);	// バッファの初期化



	GameManager* game_manager_;
	std::function<void()> on_complete_; // フェード終了時に呼ばれるコールバック

	// バッファ
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;
	std::vector<VERTEX_3D> vertices_;	// 頂点データ
	Shader shader_;						// シェーダ
	std::shared_ptr<Texture> fade_texture_;  // テクスチャ
	Vector2 current_uv_;

	int total_frame_;       // 総フレーム数 (フェード全体の再生時間をフレーム単位で表す)
	int current_frame_;     // 現在の進行中のフレーム
	float elapsed_time_;    // 累積経過時間 (秒単位)
	float frame_duration_;  // 1フレームあたりの時間 (秒単位)	bool is_loop_;				// ループするかどうか
	bool is_playing_;		// アニメーションを再生中かどうか

	bool is_loading_ = false;	// 画像が切り替わっているか

	std::unique_ptr<class AudioManager> audio_manager_;
};

#endif // FADE_MANAGER_H_