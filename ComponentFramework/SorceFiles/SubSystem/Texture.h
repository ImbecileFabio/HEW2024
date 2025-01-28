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
	DirectX::SimpleMath::Vector2 frame_size_;	// 1�t���[���̃T�C�Y

	bool loop_flg_{}; // ���[�v�t���O

	int m_width{};	// ��
	int m_height{};	// ����
	int m_bpp{};		// BPP


	int m_cutU{};	// ��������
	int m_cutV{};	// �c������
	float m_numU{};	// ���`��ʒu
	float m_numV{};	// �c�`��ʒu
	float m_anmSpeed{}; // �A�j���[�V�����X�s�[�h
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
	// �A�j���[�V�����摜�̈�}�X�̃T�C�Y���擾
	auto GetFrameSize() { return frame_size_; }


	auto GetNumU() const { return m_numU; }
	void SetNumU(float _numU) { m_numU = _numU; }
	auto GetNumV() const { return m_numV; }
	void SetNumV(float _numV) { m_numV = _numV; }

	void SetGPU();
};