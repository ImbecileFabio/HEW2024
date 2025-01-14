#pragma once

#include	<d3d11.h>
#include	<string>
#include	<wrl/client.h> // ComPtrの定義を含むヘッダファイル
#include	<filesystem>


using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//Textureクラス
//-----------------------------------------------------------------------------
class Texture
{
	std::string m_texname{}; // ファイル名
	ComPtr<ID3D11ShaderResourceView> m_srv{}; // シェーダーリソースビュー

	bool loop_flg_; // ループフラグ

	int m_width; // 幅
	int m_height; // 高さ
	int m_bpp; // BPP

	int m_cutU; // 横分割数
	int m_cutV; // 縦分割数
	int m_numU;	// 横描画位置
	int m_numV;	// 縦描画位置
	int m_anmSpeed; // アニメーションスピード
public:
	Texture(bool loopFlg = false, int _cutU = 1, int _cutV = 1, int _anmSpeed = 1);

	bool Load(const std::string& filename);
	bool LoadFromFemory(const unsigned char* data,int len);

	auto GetLoopFlg() const { return loop_flg_; }

	auto GetWidth() const { return m_width; }
	auto GetHeight() const { return m_height; }
	auto GetCutU() const { return m_cutU; }
	auto GetCutV() const { return m_cutV; }

	auto GetNumU() const { return m_numU; }
	void SetNumU(int _numU) { m_numU = _numU; }
	auto GetNumV() const { return m_numV; }
	void SetNumV(int _numV) { m_numV = _numV; }

	void SetGPU();
};