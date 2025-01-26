#pragma once

#include	<d3d11.h>
#include	<string>
#include	<wrl/client.h> // ComPtr�̒�`���܂ރw�b�_�t�@�C��
#include	<filesystem>
#include	<SimpleMath.h>


using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//Texture�N���X
//-----------------------------------------------------------------------------
class Texture
{
	std::string m_texname{}; // �t�@�C����
	ComPtr<ID3D11ShaderResourceView> m_srv{}; // �V�F�[�_�[���\�[�X�r���[

	DirectX::SimpleMath::Vector2 offset_pos_; // �I�t�Z�b�g�|�W�V����
	DirectX::SimpleMath::Vector2 offset_size_; // �I�t�Z�b�g�T�C�Y

	bool loop_flg_; // ���[�v�t���O

	int m_width;	// ��
	int m_height;	// ����
	int m_bpp;		// BPP

	float m_cutU;	// ��������
	float m_cutV;	// �c������
	float m_numU;	// ���`��ʒu
	float m_numV;	// �c�`��ʒu
	int m_anmSpeed;		// �A�j���[�V�����X�s�[�h
	int m_anmRemain;	// �A�j���[�V�����̂��܂�(��F4*3�̕�����10�������A�j���[�V�������Ȃ��ꍇ�@2)
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