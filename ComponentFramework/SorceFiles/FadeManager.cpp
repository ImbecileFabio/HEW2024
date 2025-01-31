//=================================================================
// [FadeManager.h] �t�F�[�h�}�l�[�W��
// ���ҁF
//-----------------------------------------------------------------
// �����F��ʂ��t�F�[�h�C���A�A�E�g����N���X
//=================================================================

/*----- �C���N���[�h -----*/
#include <format>

#include"FadeManager.h"

#include"GameManager.h"
#include"AudioManager.h"
#include"Renderer.h"
#include"TextureManager.h"

#include "GameObjects/GameObject.h"


//-----------------------------------------------------------------
// @brief �R���X�g���N�^
//-----------------------------------------------------------------
FadeManager::FadeManager(GameManager* _gameManager)
	:game_manager_(_gameManager)
	, is_playing_ (false)
	, is_loading_(false)
	, current_frame_(0)
	, elapsed_time_ (0.0f)
	, frame_duration_(0.0f)
{
	InitBuffers();
}

FadeManager::~FadeManager()
{
}

//-----------------------------------------------------------------
// @brief �t�F�[�h�A�E�g�J�n
//-----------------------------------------------------------------
void FadeManager::StartFadeOut(const std::string& _fadeOutTex, std::function<void()> _onComplete)
{
	fade_texture_ = TextureManager::GetInstance().GetTexture(_fadeOutTex);

	UpdateUV();

	// �o�ߎ��ԂȂǂȂǂ����Z�b�g
	current_frame_ = 0;
	elapsed_time_ = 0.0f;
	frame_duration_ = fade_texture_->GetAnmSpeed();
	total_frame_ = fade_texture_->GetTotalFrame();

	is_playing_ = true;
	is_loading_ = false;
    on_complete_ = _onComplete;





	AudioManager::GetInstance()->Play(SoundLabel_UISceneChangeSE);
}

//-----------------------------------------------------------------
// @brief �t�F�[�h�C���J�n
//-----------------------------------------------------------------
void FadeManager::StartFadeIn(const std::string& _fadeInTex, std::function<void()> _onComplete)
{
	fade_texture_ = TextureManager::GetInstance().GetTexture(_fadeInTex);

	UpdateUV();

	// �o�ߎ��ԂȂǂȂǂ����Z�b�g
	current_frame_ = 0;
	elapsed_time_ = 0.0f;
	frame_duration_ = fade_texture_->GetAnmSpeed();
	total_frame_  = fade_texture_->GetTotalFrame();
	

	is_playing_ = true;
    on_complete_ = _onComplete;

	AudioManager::GetInstance()->Play(SoundLabel_UISceneChangeSE);
}

//-----------------------------------------------------------------
// @brief �X�V����
//-----------------------------------------------------------------
void FadeManager::Update(float _deltaTime)
{
	// �Đ����łȂ���΍X�V���Ȃ�
	if (!is_playing_) return;

	// ���[�h�摜��\�����Ă���on_complete���Ăяo�������̂ł���
	if (is_loading_) { is_playing_ = false; }

	// �o�ߎ��Ԃ����Z
	elapsed_time_ += _deltaTime;

	// �o�ߎ��Ԃ���������
	if (elapsed_time_ >= frame_duration_) {
		elapsed_time_ -= frame_duration_;

		++current_frame_;
		// ���t���[�����𒴂�����
		if (current_frame_ >= total_frame_) {

			// ���[�h�摜�ɐ؂�ւ���
			SetTexture("loading_backdrop");
			is_loading_ = true;

		}
	}

	// UV���W���v�Z
	UpdateUV();

	// �t�F�[�h�������̃R�[���o�b�N���Ăяo��
	if (!is_playing_)
	{
		if (on_complete_) { on_complete_(); }
	}
}

//-----------------------------------------------------------------
// @brief �`�揈��
//-----------------------------------------------------------------
void FadeManager::Draw() {
	// �`�撆�ȊO�`�悵�Ȃ�
	if (!is_playing_) return;
	Matrix rot;
	Matrix pos;
	Matrix scale;


	rot = Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);
	pos = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	scale = Matrix::CreateScale(1920.0f, 1080.0f, 1.0f);


	Matrix worldmtx;
	worldmtx = scale * rot * pos;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();
	assert(devicecontext);


	// �g�|���W�[���Z�b�g�i�v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);



	// ����GPU�ɃZ�b�g
	vertex_buffer_.Modify(vertices_);	// �o�b�t�@�̍X�V
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();

	fade_texture_->SetGPU();

	shader_.SetGPU();

	devicecontext->DrawIndexed(
		4,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);

}

//--------------------------------------------------
// @brief UV���W���X�V
//--------------------------------------------------
void FadeManager::UpdateUV()
{

	int frameX = current_frame_ % fade_texture_->GetCutU();	// ���̕������Ŋ��������܂�
	int frameY = current_frame_ / fade_texture_->GetCutU();	// ���̕������Ŋ�������

	Vector2 frameSize = fade_texture_->GetFrameSize();

	current_uv_ = { frameX * frameSize.x, frameY * frameSize.y };

	Vector2 uvMin = current_uv_;
	Vector2 uvMax = { current_uv_.x + frameSize.x, current_uv_.y + frameSize.y };

	vertices_[0].uv = { uvMin.x, uvMin.y };
	vertices_[1].uv = { uvMax.x, uvMin.y };
	vertices_[2].uv = { uvMin.x, uvMax.y };
	vertices_[3].uv = { uvMax.x, uvMax.y };

}

void FadeManager::InitBuffers(float _cutU, float _cutV)
{
	// ���_�f�[�^

	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices_[1].position = Vector3(0.5f, 0.5f, 0.0f);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices_[3].position = Vector3(0.5f, -0.5f, 0.0f);

	vertices_[0].color = Color(1, 1, 1, 1);
	vertices_[1].color = Color(1, 1, 1, 1);
	vertices_[2].color = Color(1, 1, 1, 1);
	vertices_[3].color = Color(1, 1, 1, 1);

	vertices_[0].uv = Vector2(0.0f, 0.0f);
	vertices_[1].uv = Vector2(1.0f, 0.0f);
	vertices_[2].uv = Vector2(0.0f, 1.0f);
	vertices_[3].uv = Vector2(1.0f, 1.0f);

	// ���_�o�b�t�@����
	vertex_buffer_.Create(vertices_);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// �C���f�b�N�X�o�b�t�@����
	index_buffer_.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	shader_.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
}
