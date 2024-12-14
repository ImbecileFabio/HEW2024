//==================================================
// [ConstantBuffer.h] �萔�o�b�t�@
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���@�[�e�b�N�X���󂯓n�����߂̂��
//==================================================
#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"../Renderer.h"

using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//ConstantBuffer�N���X
//-----------------------------------------------------------------------------
template <typename T>
class ConstantBuffer {

	ComPtr<ID3D11Buffer> constant_buffer_;

public:
	void Create(const std::vector<T>& buffers) {

		// �f�o�C�X�擾
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);

		// �萔�o�b�t�@�̐ݒ�
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = buffers.size(); // �萔�o�b�t�@�\���̂̃T�C�Y
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0; // �f�t�H���g�g�p�̏ꍇ�ACPU�A�N�Z�X�͕s�v

		// �萔�o�b�t�@���쐬
		hr = device->CreateBuffer(&bufferDesc, nullptr, constantBuffer);
		if (FAILED(hr)) {
			return false; // �o�b�t�@�쐬���s
		}


		assert(sts == true);
	}

	// GPU�ɃZ�b�g
	void SetGPU() {

		// �f�o�C�X�R���e�L�X�g�擾
		ID3D11DeviceContext* devicecontext = nullptr;
		devicecontext = Renderer::GetDeviceContext();

		// ���_�o�b�t�@���Z�b�g����
		unsigned int stride = sizeof(T);
		unsigned  offset = 0;
		devicecontext->IASetConstantBuffers(0, 1, constant_buffer_.GetAddressOf(), &stride, &offset);

	}

};
#endif // CONSTANT_BUFFER_H_