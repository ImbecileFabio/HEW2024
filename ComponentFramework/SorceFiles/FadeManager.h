//=================================================================
// [FadeManager.h] �t�F�[�h�}�l�[�W��
// ���ҁF
//-----------------------------------------------------------------
// �����F��ʂ��t�F�[�h�C���A�A�E�g����N���X
//=================================================================
#ifndef FADE_MANAGER_H_
#define FADE_MANAGER_H_

/*----- �C���N���[�h -----*/
#include <wrl/client.h>
#include <functional>
#include <string>
#include <memory>

#include <SimpleMath.h>

#include "TextureManager.h"

#include "SubSystem/Shader.h"
#include "SubSystem/VertexBuffer.h"
#include "SubSystem/IndexBuffer.h"
#include "SubSystem/Texture.h"

using namespace DirectX::SimpleMath;

/*----- �񋓌^ -----*/
enum class FadeType
{
	In,
	Out
};

/*----- �\���̒�` -----*/


/*----- �O���錾 -----*/
class GameManager;
//-----------------------------------------------------------------
// �t�F�[�h�}�l�[�W���N���X
//-----------------------------------------------------------------
class FadeManager {
public:
	FadeManager(GameManager* _gameManager);
	~FadeManager();

	

	// �t�F�[�h�A�E�g�J�n
	void StartFadeOut(const std::string& _fadeOutTex, std::function<void()> on_complete = nullptr);
	// �t�F�[�h�C���J�n
	void StartFadeIn(const std::string& _fadeInTex, std::function<void()> on_complete = nullptr);

	void Update(float delta_time);
	void Draw();

	void UpdateUV();

	bool GetIsPlaying() const { return is_playing_; } // �t�F�[�h�����ǂ���

	void SetTexture(const std::string& _textureName) { fade_texture_ = TextureManager::GetInstance().GetTexture(_textureName); }

private:
	void InitBuffers(float _cutU = 1, float _cutV = 1);	// �o�b�t�@�̏�����



	GameManager* game_manager_;
	std::function<void()> on_complete_; // �t�F�[�h�I�����ɌĂ΂��R�[���o�b�N

	// �o�b�t�@
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;
	std::vector<VERTEX_3D> vertices_;	// ���_�f�[�^
	Shader shader_;						// �V�F�[�_
	std::shared_ptr<Texture> fade_texture_;  // �e�N�X�`��
	Vector2 current_uv_;

	int total_frame_;       // ���t���[���� (�t�F�[�h�S�̂̍Đ����Ԃ��t���[���P�ʂŕ\��)
	int current_frame_;     // ���݂̐i�s���̃t���[��
	float elapsed_time_;    // �ݐόo�ߎ��� (�b�P��)
	float frame_duration_;  // 1�t���[��������̎��� (�b�P��)	bool is_loop_;				// ���[�v���邩�ǂ���
	bool is_playing_;		// �A�j���[�V�������Đ������ǂ���

	bool is_loading_ = false;	// �摜���؂�ւ���Ă��邩

	std::unique_ptr<class AudioManager> audio_manager_;
};

#endif // FADE_MANAGER_H_