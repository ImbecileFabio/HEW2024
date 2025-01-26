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
#include <SimpleMath.h>

#include <functional>
#include <string>

#include "SubSystem/Shader.h"

/*----- �񋓌^ -----*/
enum class FadeType
{
	In,
	Out
};

/*----- �\���̒�` -----*/
struct FadeParams {
   float fadeProgress;
   DirectX::XMFLOAT2 center;
   float edgeWidth;
   BOOL isFadeOut;  
};

/*----- �O���錾 -----*/
class GameManager;
//-----------------------------------------------------------------
// �t�F�[�h�}�l�[�W���N���X
//-----------------------------------------------------------------
class FadeManager {
public:
    FadeManager( GameManager* _gameManager);

    void StartFadeOut(float duration, std::function<void()> on_complete = nullptr);
    void StartFadeIn(float duration, std::function<void()> on_complete = nullptr);

    void Update(float delta_time);
    void Draw();

    void UpdateFadeParams(ID3D11DeviceContext* _context, const FadeParams& _params);

    void SetTextures(ID3D11DeviceContext* _context, ID3D11ShaderResourceView* _sceneTexture, ID3D11ShaderResourceView* _maskTexture);

	bool GetIsFading() const { return is_fading_; } // �t�F�[�h�����ǂ���
    float GetFadeProgress() const;

    void InitBuffer();

private:
	GameManager* game_manager_;

	FadeParams fade_params_; // �t�F�[�h�̃p�����[�^

    std::function<void()> on_complete_; // �t�F�[�h�I�����ɌĂ΂��R�[���o�b�N

    FadeType fade_type_;        // "in" �܂��� "out"
    float fade_duration_;          // �t�F�[�h�̑S�̎���
    float elapsed_time_;           // ���݂̌o�ߎ���
    bool is_fading_;               // �t�F�[�h�����ǂ���

	Microsoft::WRL::ComPtr<ID3D11Buffer> fade_params_buffer_; // ���_�o�b�t�@
	Shader shader_;               // �t�F�[�h�p�̃V�F�[�_
};

#endif // FADE_MANAGER_H_