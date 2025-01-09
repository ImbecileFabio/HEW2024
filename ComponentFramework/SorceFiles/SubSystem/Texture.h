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

	int m_texU; // テクスチャU
	int m_texV; // テクスチャV
	int m_anmSpeed; // アニメーションスピード
public:
	Texture(bool loopFlg = false, int _texU = 0, int _texV = 0, int _anmSpeed = 1);

	bool Load(const std::string& filename);
	bool LoadFromFemory(const unsigned char* data,int len);

	auto GetWidth() const { return m_width; }
	auto GetHeight() const { return m_height; }

	void SetGPU();
};