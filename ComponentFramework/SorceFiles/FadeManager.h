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
#include <SimpleMath.h>

#include <functional>
#include <string>

#include "SubSystem/Shader.h"

/*----- 列挙型 -----*/
enum class FadeType
{
	In,
	Out
};

/*----- 構造体定義 -----*/
struct FadeParams {
   float fadeProgress;
   DirectX::XMFLOAT2 center;
   float edgeWidth;
   BOOL isFadeOut;  
};

/*----- 前方宣言 -----*/
class GameManager;
//-----------------------------------------------------------------
// フェードマネージャクラス
//-----------------------------------------------------------------
class FadeManager {
public:
    FadeManager( GameManager* _gameManager);

    void StartFadeOut(float duration, std::function<void()> on_complete = nullptr);
    void StartFadeIn(float duration, std::function<void()> on_complete = nullptr);

    void Update(float delta_time);
    void Draw();

    void UpdateFadeParams(ID3D11DeviceContext* _context, const FadeParams& _params);

    void SetTextures(ID3D11DeviceContext* _context, ID3D11ShaderResourceView* _sceneTexture, ID3D11ShaderResourceView* _maskTexture);

	bool GetIsFading() const { return is_fading_; } // フェード中かどうか
    float GetFadeProgress() const;

    void InitBuffer();

private:
	GameManager* game_manager_;

	FadeParams fade_params_; // フェードのパラメータ

    std::function<void()> on_complete_; // フェード終了時に呼ばれるコールバック

    FadeType fade_type_;        // "in" または "out"
    float fade_duration_;          // フェードの全体時間
    float elapsed_time_;           // 現在の経過時間
    bool is_fading_;               // フェード中かどうか

	Microsoft::WRL::ComPtr<ID3D11Buffer> fade_params_buffer_; // 頂点バッファ
	Shader shader_;               // フェード用のシェーダ
};

#endif // FADE_MANAGER_H_