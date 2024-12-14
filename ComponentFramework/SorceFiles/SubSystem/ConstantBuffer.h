//==================================================
// [ConstantBuffer.h] 定数バッファ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ヴァーテックスを受け渡すためのやつ
//==================================================
#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"../Renderer.h"

using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//ConstantBufferクラス
//-----------------------------------------------------------------------------
template <typename T>
class ConstantBuffer {

	ComPtr<ID3D11Buffer> constant_buffer_;

public:
	void Create(const std::vector<T>& _constantBuffer) {

		// デバイス取得
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

	// GPUにセット
	void SetGPU() {

		// デバイスコンテキスト取得
		ID3D11DeviceContext* devicecontext = nullptr;
		devicecontext = Renderer::GetDeviceContext();

		// 頂点バッファをセットする
		unsigned int stride = sizeof(T);
		unsigned  offset = 0;
        devicecontext->GSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());

	}

};
#endif // CONSTANT_BUFFER_H_