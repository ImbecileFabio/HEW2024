#pragma once

#include	<d3d11.h>
#include	<string>
#include	<wrl/client.h> // ComPtr�̒�`���܂ރw�b�_�t�@�C��
#include	<filesystem>


using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//Texture�N���X
//-----------------------------------------------------------------------------
class Texture
{
	std::string m_texname{}; // �t�@�C����
	ComPtr<ID3D11ShaderResourceView> m_srv{}; // �V�F�[�_�[���\�[�X�r���[

	bool loop_flg_; // ���[�v�t���O

	int m_width; // ��
	int m_height; // ����
	int m_bpp; // BPP

	int m_texU; // �e�N�X�`��U
	int m_texV; // �e�N�X�`��V
	int m_anmSpeed; // �A�j���[�V�����X�s�[�h
public:
	Texture(bool loopFlg = false, int _texU = 0, int _texV = 0, int _anmSpeed = 1);

	bool Load(const std::string& filename);
	bool LoadFromFemory(const unsigned char* data,int len);

	auto GetWidth() const { return m_width; }
	auto GetHeight() const { return m_height; }

	void SetGPU();
};