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

	int m_width;	// ��
	int m_height;	// ����
	int m_bpp;		// BPP

	float m_cutU;	// ��������
	float m_cutV;	// �c������
	float m_numU;	// ���`��ʒu
	float m_numV;	// �c�`��ʒu
	int m_anmSpeed; // �A�j���[�V�����X�s�[�h
public:
	Texture(bool loopFlg, float _cutU, float _cutV, int _anmSpeed);

	bool Load(const std::string& filename);
	bool LoadFromFemory(const unsigned char* data,int len);

	auto GetLoopFlg() const { return loop_flg_; }

	auto GetWidth() const { return m_width; }
	auto GetHeight() const { return m_height; }
	auto GetCutU() const { return m_cutU; }
	auto GetCutV() const { return m_cutV; }
	auto GetAnmSpeed() const { return m_anmSpeed; }

	auto GetNumU() const { return m_numU; }
	void SetNumU(float _numU) { m_numU = _numU; }
	auto GetNumV() const { return m_numV; }
	void SetNumV(float _numV) { m_numV = _numV; }

	void SetGPU();
};