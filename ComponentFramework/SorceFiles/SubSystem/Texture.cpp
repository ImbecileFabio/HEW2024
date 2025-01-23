#include	<iostream>
#include	"Texture.h"
#include	"stb_image.h"
#include	"../Renderer.h"

Texture::Texture(const DirectX::SimpleMath::Vector2& _offsetPos, const DirectX::SimpleMath::Vector2& _offsetSize, bool _loopFlg, float _cutU, float _cutV, float _anmSpeed)
	: offset_pos_(_offsetPos)
	, offset_size_(_offsetSize)
	, loop_flg_(_loopFlg)
	, m_cutU(_cutU)
	, m_cutV(_cutV)
	, m_anmSpeed(_anmSpeed)
{
	m_frameSize.x = 1.0f / m_cutU;
	m_frameSize.y = 1.0f / m_cutV;
}

// �e�N�X�`�������[�h
bool Texture::Load(const std::string& filename)
{
	bool sts = true;
	unsigned char* pixels;

	// �摜�ǂݍ���
	pixels = stbi_load(filename.c_str(), &m_width, &m_height, &m_bpp, 4);
	if (pixels == nullptr) {
		std::cout << filename.c_str() << " Load error " << std::endl;
		return false;
	}

	// �e�N�X�`��2D���\�[�X����
	ComPtr<ID3D11Texture2D> pTexture;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = m_width;
	desc.Height = m_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// RGBA
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;			// RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::GetDevice();

	HRESULT hr = device->CreateTexture2D(&desc, &subResource, pTexture.GetAddressOf());
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// SRV����
	hr = device->CreateShaderResourceView(pTexture.Get(), nullptr, m_srv.GetAddressOf());
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// �s�N�Z���C���[�W���
	stbi_image_free(pixels);

	return true;
}

// �e�N�X�`�������������烍�[�h
bool Texture::LoadFromFemory(const unsigned char* Data,int len) {

	bool sts = true;
	unsigned char* pixels;

	// �摜�ǂݍ���
	pixels = stbi_load_from_memory(Data, 
		len, 
		&m_width, 
		&m_height, 
		&m_bpp, 
		STBI_rgb_alpha);

	// �e�N�X�`��2D���\�[�X����
	ComPtr<ID3D11Texture2D> pTexture;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = m_width;
	desc.Height = m_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// RGBA
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource{};
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;			// RGBA = 4 bytes per pixel
	subResource.SysMemSlicePitch = 0;

	ID3D11Device* device = Renderer::GetDevice();

	HRESULT hr = device->CreateTexture2D(&desc, &subResource, pTexture.GetAddressOf());
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// SRV����
	hr = device->CreateShaderResourceView(pTexture.Get(), nullptr, m_srv.GetAddressOf());
	if (FAILED(hr)) {
		stbi_image_free(pixels);
		return false;
	}

	// �s�N�Z���C���[�W���
	stbi_image_free(pixels);

	return true;
}

// �e�N�X�`����GPU�ɃZ�b�g
void Texture::SetGPU()
{
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();
	devicecontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
}
