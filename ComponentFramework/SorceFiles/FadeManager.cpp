//=================================================================
// [FadeManager.h] フェードマネージャ
// 著者：
//-----------------------------------------------------------------
// 説明：画面をフェードイン、アウトするクラス
//=================================================================

/*----- インクルード -----*/
#include <format>

#include"FadeManager.h"

#include"GameManager.h"
#include"AudioManager.h"
#include"Renderer.h"
#include"TextureManager.h"

#include "GameObjects/GameObject.h"


//-----------------------------------------------------------------
// @brief コンストラクタ
//-----------------------------------------------------------------
FadeManager::FadeManager(GameManager* _gameManager)
	:game_manager_(_gameManager)
	, is_playing_ (false)
	, is_loading_(false)
	, current_frame_(0)
	, elapsed_time_ (0.0f)
	, frame_duration_(0.0f)
{
	InitBuffers();
}

FadeManager::~FadeManager()
{
}

//-----------------------------------------------------------------
// @brief フェードアウト開始
//-----------------------------------------------------------------
void FadeManager::StartFadeOut(const std::string& _fadeOutTex, std::function<void()> _onComplete)
{
	fade_texture_ = TextureManager::GetInstance().GetTexture(_fadeOutTex);

	UpdateUV();

	// 経過時間などなどをリセット
	current_frame_ = 0;
	elapsed_time_ = 0.0f;
	frame_duration_ = fade_texture_->GetAnmSpeed();
	total_frame_ = fade_texture_->GetTotalFrame();

	is_playing_ = true;
	is_loading_ = false;
    on_complete_ = _onComplete;





	AudioManager::GetInstance()->Play(SoundLabel_UISceneChangeSE);
}

//-----------------------------------------------------------------
// @brief フェードイン開始
//-----------------------------------------------------------------
void FadeManager::StartFadeIn(const std::string& _fadeInTex, std::function<void()> _onComplete)
{
	fade_texture_ = TextureManager::GetInstance().GetTexture(_fadeInTex);

	UpdateUV();

	// 経過時間などなどをリセット
	current_frame_ = 0;
	elapsed_time_ = 0.0f;
	frame_duration_ = fade_texture_->GetAnmSpeed();
	total_frame_  = fade_texture_->GetTotalFrame();
	

	is_playing_ = true;
    on_complete_ = _onComplete;

	AudioManager::GetInstance()->Play(SoundLabel_UISceneChangeSE);
}

//-----------------------------------------------------------------
// @brief 更新処理
//-----------------------------------------------------------------
void FadeManager::Update(float _deltaTime)
{
	// 再生中でなければ更新しない
	if (!is_playing_) return;

	// ロード画像を表示してからon_completeを呼び出したいのでここ
	if (is_loading_) { is_playing_ = false; }

	// 経過時間を加算
	elapsed_time_ += _deltaTime;

	// 経過時間が超えたら
	if (elapsed_time_ >= frame_duration_) {
		elapsed_time_ -= frame_duration_;

		++current_frame_;
		// 総フレーム数を超えたら
		if (current_frame_ >= total_frame_) {

			// ロード画像に切り替える
			SetTexture("loading_backdrop");
			is_loading_ = true;

		}
	}

	// UV座標を計算
	UpdateUV();

	// フェード完了時のコールバックを呼び出し
	if (!is_playing_)
	{
		if (on_complete_) { on_complete_(); }
	}
}

//-----------------------------------------------------------------
// @brief 描画処理
//-----------------------------------------------------------------
void FadeManager::Draw() {
	// 描画中以外描画しない
	if (!is_playing_) return;
	Matrix rot;
	Matrix pos;
	Matrix scale;


	rot = Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);
	pos = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	scale = Matrix::CreateScale(1920.0f, 1080.0f, 1.0f);


	Matrix worldmtx;
	worldmtx = scale * rot * pos;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();
	assert(devicecontext);


	// トポロジーをセット（プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);



	// 情報をGPUにセット
	vertex_buffer_.Modify(vertices_);	// バッファの更新
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();

	fade_texture_->SetGPU();

	shader_.SetGPU();

	devicecontext->DrawIndexed(
		4,							// 描画するインデックス数（四角形なんで４）
		0,							// 最初のインデックスバッファの位置
		0);

}

//--------------------------------------------------
// @brief UV座標を更新
//--------------------------------------------------
void FadeManager::UpdateUV()
{

	int frameX = current_frame_ % fade_texture_->GetCutU();	// 横の分割数で割ったあまり
	int frameY = current_frame_ / fade_texture_->GetCutU();	// 横の分割数で割った商

	Vector2 frameSize = fade_texture_->GetFrameSize();

	current_uv_ = { frameX * frameSize.x, frameY * frameSize.y };

	Vector2 uvMin = current_uv_;
	Vector2 uvMax = { current_uv_.x + frameSize.x, current_uv_.y + frameSize.y };

	vertices_[0].uv = { uvMin.x, uvMin.y };
	vertices_[1].uv = { uvMax.x, uvMin.y };
	vertices_[2].uv = { uvMin.x, uvMax.y };
	vertices_[3].uv = { uvMax.x, uvMax.y };

}

void FadeManager::InitBuffers(float _cutU, float _cutV)
{
	// 頂点データ

	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices_[1].position = Vector3(0.5f, 0.5f, 0.0f);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices_[3].position = Vector3(0.5f, -0.5f, 0.0f);

	vertices_[0].color = Color(1, 1, 1, 1);
	vertices_[1].color = Color(1, 1, 1, 1);
	vertices_[2].color = Color(1, 1, 1, 1);
	vertices_[3].color = Color(1, 1, 1, 1);

	vertices_[0].uv = Vector2(0.0f, 0.0f);
	vertices_[1].uv = Vector2(1.0f, 0.0f);
	vertices_[2].uv = Vector2(0.0f, 1.0f);
	vertices_[3].uv = Vector2(1.0f, 1.0f);

	// 頂点バッファ生成
	vertex_buffer_.Create(vertices_);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	index_buffer_.Create(indices);

	// シェーダオブジェクト生成
	shader_.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
}
