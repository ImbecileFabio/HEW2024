//=================================================================
// [FadeManager.h] �t�F�[�h�}�l�[�W��
// ���ҁF
//-----------------------------------------------------------------
// �����F��ʂ��t�F�[�h�C���A�A�E�g����N���X
//=================================================================

#include "FadeManager.h"
#include <algorithm>
#include <iostream>

#include "GameManager.h"
#include "SubSystem/Shader.h"

//-----------------------------------------------------------------
// @brief �R���X�g���N�^
//-----------------------------------------------------------------
FadeManager::FadeManager(GameManager* _gameManager)
	: game_manager_(_gameManager)
    , fade_duration_(0.0f)
    , elapsed_time_(0.0f)
    , is_fading_(false)
    , fade_type_(FadeType::Out)
    , on_complete_(nullptr)
{
	InitBuffer();
}

//-----------------------------------------------------------------
// @brief �t�F�[�h�A�E�g�J�n
//-----------------------------------------------------------------
void FadeManager::StartFadeOut(float duration, std::function<void()> on_complete) {
    fade_duration_ = duration;
    elapsed_time_ = 0.0f;
    is_fading_ = true;
    fade_type_ = FadeType::Out;
    on_complete_ = on_complete;
}

//-----------------------------------------------------------------
// @brief �t�F�[�h�C���J�n
//-----------------------------------------------------------------
void FadeManager::StartFadeIn(float duration, std::function<void()> on_complete) {
    fade_duration_ = duration;
    elapsed_time_ = 0.0f;
    is_fading_ = true;
    fade_type_ = FadeType::In;
    on_complete_ = on_complete;
}

//-----------------------------------------------------------------
// @brief �X�V����
//-----------------------------------------------------------------
void FadeManager::Update(float delta_time) {
    if (!is_fading_) return;

    elapsed_time_ += delta_time;
    if (elapsed_time_ >= fade_duration_) {
        is_fading_ = false;
        elapsed_time_ = fade_duration_;
        if (on_complete_) {
            on_complete_();
        }
    }
}

//-----------------------------------------------------------------
// @brief �`�揈��
//-----------------------------------------------------------------
void FadeManager::Draw()
{
	if (!is_fading_) return;
	float progress = GetFadeProgress();
    float alpha = fade_type_ == FadeType::Out ? progress : (1.0f - progress);

    
}

//-----------------------------------------------------------------
// @brief �t�F�[�h�p�����[�^�̍X�V
//-----------------------------------------------------------------
void FadeManager::UpdateFadeParams(ID3D11DeviceContext* _context, const FadeParams& _params)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource = {};
    _context->Map(fade_params_buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy(mappedResource.pData, &_params, sizeof(FadeParams));
    _context->Unmap(fade_params_buffer_.Get(), 0);

    _context->PSSetConstantBuffers(0, 5, fade_params_buffer_.GetAddressOf());
}

//-----------------------------------------------------------------
// @brief �e�N�X�`���̃Z�b�g
//-----------------------------------------------------------------
void FadeManager::SetTextures(ID3D11DeviceContext* _context, ID3D11ShaderResourceView* _sceneTexture, ID3D11ShaderResourceView* _maskTexture)
{
	ID3D11ShaderResourceView* textures[] = { _sceneTexture, _maskTexture };
	_context->PSSetShaderResources(0, 2, textures);
}


//-----------------------------------------------------------------
// @brief �t�F�[�h�̐i�s�x���擾
//-----------------------------------------------------------------
float FadeManager::GetFadeProgress() const {
    if (!is_fading_ || fade_duration_ == 0.0f) return 0.0f;
    return std::clamp(elapsed_time_ / fade_duration_, 0.0f, 1.0f);
}

//-----------------------------------------------------------------
// @brief �o�b�t�@�Ȃǂ̏�����
//-----------------------------------------------------------------
void FadeManager::InitBuffer()
{
	// �o�b�t�@�̐���
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = sizeof(FadeParams);
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Renderer::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &fade_params_buffer_);

    // �V�F�[�_�̐���
    shader_.CreateFade("FadePS.hlsl");

}
