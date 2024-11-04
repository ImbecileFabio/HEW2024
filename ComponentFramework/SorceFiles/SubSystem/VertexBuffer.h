//==================================================
// [VertexBuffer.h] ヴァーテックスバッファ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ヴァーテックスを受け渡すためのやつ
//==================================================
#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"../Renderer.h"

using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//VertexBufferクラス
//-----------------------------------------------------------------------------
template <typename T>
class VertexBuffer {

	ComPtr<ID3D11Buffer> vertex_buffer_;

public:
	void Create(const std::vector<T>& vertices) {

		// デバイス取得
		ID3D11Device* device = nullptr;
		device = Renderer::GetDevice();
		assert(device);

		// 頂点バッファ作成
		bool sts = CreateVertexBufferWrite(
			device,
			sizeof(T),						// １頂点当たりバイト数
			(unsigned int)vertices.size(),	// 頂点数
			(void*)vertices.data(),			// 頂点データ格納メモリ先頭アドレス
			&vertex_buffer_);				// 頂点バッファ

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
		devicecontext->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), &stride, &offset);

	}

	// 頂点バッファを書き換える
	void Modify(const std::vector<T>& vertices)
	{
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		HRESULT hr = Renderer::GetDeviceContext()->Map(
			vertex_buffer_.Get(),
			0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		if (SUCCEEDED(hr)) {
			memcpy(msr.pData, vertices.data(), vertices.size() * sizeof(T));
			Renderer::GetDeviceContext()->Unmap(vertex_buffer_.Get(), 0);
		}
	}
};

#endif // VERTEX_BUFFER_H_
//==================================================
//				End of FIle
//==================================================