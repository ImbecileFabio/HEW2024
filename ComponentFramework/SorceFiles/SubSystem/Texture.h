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

	bool loop_flg_; // ループフラグ

	int m_width;	// 幅
	int m_height;	// 高さ
	int m_bpp;		// BPP

	float m_cutU;	// 横分割数
	float m_cutV;	// 縦分割数
	float m_numU;	// 横描画位置
	float m_numV;	// 縦描画位置
	int m_anmSpeed;		// アニメーションスピード
	int m_anmRemain;	// アニメーションのあまり(例：4*3の分割で10枚しかアニメーションがない場合　2)
public:
	Texture(const DirectX::SimpleMath::Vector2& _offsetPos, const DirectX::SimpleMath::Vector2& _offsetSize,
			bool _loopFlg, float _cutU, float _cutV, int _anmSpeed, int _anmRemain);

	bool Load(const std::string& filename);
	bool LoadFromFemory(const unsigned char* data,int len);

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
	auto GetAnmRemain() const { return m_anmRemain; }

	auto GetNumU() const { return m_numU; }
	void SetNumU(float _numU) { m_numU = _numU; }
	auto GetNumV() const { return m_numV; }
	void SetNumV(float _numV) { m_numV = _numV; }

	void SetGPU();
};