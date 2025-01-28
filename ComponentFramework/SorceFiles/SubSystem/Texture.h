#pragma once

#include	<d3d11.h>
#include	<string>
#include	<wrl/client.h> // ComPtrの定義を含むヘッダファイル
#include	<filesystem>
#include	<SimpleMath.h>


using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//Textureクラス
//-----------------------------------------------------------------------------
class Texture
{
	std::string m_texname{}; // ファイル名
	ComPtr<ID3D11ShaderResourceView> m_srv{}; // シェーダーリソースビュー

	DirectX::SimpleMath::Vector2 offset_pos_; // オフセットポジション
	DirectX::SimpleMath::Vector2 offset_size_; // オフセットサイズ
	DirectX::SimpleMath::Vector2 frame_size_;	// 1フレームのサイズ

	bool loop_flg_{}; // ループフラグ

	int m_width{};	// 幅
	int m_height{};	// 高さ
	int m_bpp{};		// BPP


	int m_cutU{};	// 横分割数
	int m_cutV{};	// 縦分割数
	float m_numU{};	// 横描画位置
	float m_numV{};	// 縦描画位置
	float m_anmSpeed{}; // アニメーションスピード
public:
	Texture(const DirectX::SimpleMath::Vector2& _offsetPos = {0.0f, 0.0f}, const DirectX::SimpleMath::Vector2& _offsetSize = {0.0f, 0.0f}, bool _loopFlg = false, int _cutU = 1, int _cutV = 1, float _anmSpeed = 0.1f);

	bool Load(const std::string& filename);
	bool LoadFromFemory(const unsigned char* data,int len);

	auto GetSRV() const { return m_srv; }

	auto GetOffsetPos() const { return offset_pos_; }
	void SetOffsetPos(const DirectX::SimpleMath::Vector2& _offsetPos) { offset_pos_ = _offsetPos; }
	auto GetOffsetSize() const { return offset_size_; }
	void SetOffsetSize(const DirectX::SimpleMath::Vector2& _offsetSize) { offset_size_ = _offsetSize; }

	auto GetLoopFlg() const { return loop_flg_; }

	auto GetWidth() const { return m_width; }
	auto GetHeight() const { return m_height; }
	auto GetCutU() const { return m_cutU; }
	auto GetCutV() const { return m_cutV; }
	auto GetAnmSpeed() const { return m_anmSpeed; }
	// アニメーション画像の一マスのサイズを取得
	auto GetFrameSize() { return frame_size_; }


	auto GetNumU() const { return m_numU; }
	void SetNumU(float _numU) { m_numU = _numU; }
	auto GetNumV() const { return m_numV; }
	void SetNumV(float _numV) { m_numV = _numV; }

	void SetGPU();
};