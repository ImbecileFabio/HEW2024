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
	void Create(const std::vector<T>& _constantBuffer) {

		// �f�o�C�X�擾
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);

		bool sts = CreateConstantBuffer(
			device,
			sizeof(T),
			&constant_buffer_
			);
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
        devicecontext->GSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());

	}

};
#endif // CONSTANT_BUFFER_H_