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

	int m_cutU; // ��������
	int m_cutV; // �c������
	int m_numU;	// ���`��ʒu
	int m_numV;	// �c�`��ʒu
	int m_anmSpeed; // �A�j���[�V�����X�s�[�h
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