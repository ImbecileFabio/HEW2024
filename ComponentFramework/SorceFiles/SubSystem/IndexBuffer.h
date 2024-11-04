//==================================================
// [IndexBuffer.h] インデックスバッファー
// 著者：有馬啓太
//--------------------------------------------------
// 説明：インデックスを受け渡すためのやつ
//==================================================
#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include	<vector>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"../Renderer.h"

using Microsoft::WRL::ComPtr;

//-----------------------------------------------------------------------------
//IndexBufferクラス
//-----------------------------------------------------------------------------
class IndexBuffer {

	ComPtr<ID3D11Buffer> m_IndexBuffer;

public:
	void Create(const std::vector<unsigned int>& indices) {

		// デバイス取得
		ID3D11Device* device = nullptr;

		device = Renderer::GetDevice();

		assert(device);

		// インデックスバッファ作成
		bool sts = CreateIndexBuffer(
			device,										// デバイス
			(unsigned int)(indices.size()),				// インデックス数
			(void*)indices.data(),						// インデックスデータ先頭アドレス
			&m_IndexBuffer);							// インデックスバッファ

		assert(sts == true);
	}

	void SetGPU() {
		// デバイスコンテキスト取得
		ID3D11DeviceContext* devicecontext = nullptr;
		devicecontext = Renderer::GetDeviceContext();

		// インデックスバッファをセット
		devicecontext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	}
};

#endif // INDEX_BUFFER_H_
//==================================================
//				End of FIle
//==================================================