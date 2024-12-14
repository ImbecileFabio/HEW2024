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
	void Create(const std::vector<T>& buffers) {

		// デバイス取得
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);

		// 定数バッファの設定
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = buffers.size(); // 定数バッファ構造体のサイズ
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0; // デフォルト使用の場合、CPUアクセスは不要

		// 定数バッファを作成
		hr = device->CreateBuffer(&bufferDesc, nullptr, constantBuffer);
		if (FAILED(hr)) {
			return false; // バッファ作成失敗
		}


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
		devicecontext->IASetConstantBuffers(0, 1, constant_buffer_.GetAddressOf(), &stride, &offset);

	}

};
#endif // CONSTANT_BUFFER_H_