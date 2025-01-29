
//=================================================================
// [TextureManager.h] �e�N�X�`���Ǘ��N���X
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�e�N�X�`���̃��\�[�X�Ǘ����s���N���X
//		 �V���O���g���ł̎����ł�
//=================================================================
#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#define TEXTURE_PATH "Asset/Texture/"
#define SCENE_PATH	 "Asset/Texture/scene/"
#define UI_PATH		 "Asset/Texture/scene/stageUI/"
#define BACKDROP_PATH "Asset/Texture/backdrop/"

#define TILE_PATH	 "Asset/Texture/tile/"
#define ROBOT_PATH	 "Asset/Texture/robot/"
#define GIMMICK_PATH "Asset/Texture/gimmick/"


/*----- �C���N���[�h -----*/
#include <unordered_map>
#include <string>
#include <wrl/client.h>
#include <d3d11.h>
#include <memory>

#include <SimpleMath.h>

#include "SubSystem/Texture.h"

using namespace DirectX::SimpleMath;

/*----- �\���̒�` -----*/
struct TextureInfo {
	std::string filePath;	// �t�@�C���p�X
	Vector2 offsetPos;
	Vector2 offsetSize;
	bool loop;				// ���[�v�t���O
	int cutU;				// ��������
	int cutV;				// �c������	
	float animationSpeed;	// �A�j���[�V�����X�s�[�h
	int totalFrame;			// ���t���[����
};
/*----- �O���錾 -----*/



//-----------------------------------------------------------------
// �e�N�X�`���}�l�[�W�� 
//-----------------------------------------------------------------
class TextureManager
{
public:


	// �C���X�^���X�擾
	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}

	void Init();
	void Uninit();


	// �e�N�X�`���̎擾
	std::shared_ptr<Texture> GetTexture(const std::string& _imgName);

private:
	// �V���O���g���Ȃ̂�private��
	TextureManager();
	~TextureManager();

	// �e�N�X�`���̏���ێ�
	void RegisterTextureInfo(const std::string& _textureName, const TextureInfo& _textureInfo);

	// �e�N�X�`���̓o�^
	void RegisterTexture(const std::string& _imgName, const std::string& _fileName, const DirectX::SimpleMath::Vector2& _offsetPos, const DirectX::SimpleMath::Vector2& _offsetSize, bool _loopFlg = false, int _cutU = 1, int _cutV = 1, float _anmSpeed = 0.1f, int _totalFrame = 1);	// ���ׂ�
	void RegisterTexture(const std::string& _imgName, const std::string& _fileName, bool _loopFlg = false, int _cutU = 1, int _cutV = 1, float _anmSpeed = 0.1f, int _totalFrame = 1);// �I�t�Z�b�g�Ȃ�

	// �e�N�X�`���̏��o�^
	void RegisterAllTextures();
	// �������
	void ClearCache(void);

	// �e�N�X�`�����
	std::unordered_map<std::string, TextureInfo> texture_info_;
	// �e�N�X�`���L���b�V��
	std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache_;

	// LRU�L���b�V���Ǘ��p
	std::list<std::string> lru_list_;
	std::unordered_map<std::string, std::list<std::string>::iterator> lru_map_;
	size_t max_cache_size_ = 20; // �ő�L���b�V���T�C�Y

};


#endif TEXTURE_MANAGER_H_