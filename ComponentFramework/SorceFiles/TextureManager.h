
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

#include "SubSystem/Texture.h"

/*----- �\���̒�` -----*/

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

	// �e�N�X�`���̓o�^
	bool RegisterTexture(const std::string& _imgName, const std::string& _fileName);
	// �e�N�X�`���̎擾
	std::shared_ptr<Texture> GetTexture(const std::string& _imgName);


private:
	// �V���O���g���Ȃ̂�private��
	TextureManager();
	~TextureManager();

	// �e�N�X�`���̑S�o�^
	void RegisterAllTextures();
	// �������
	void ClearCache(void);

	// �e�N�X�`���L���b�V��
	std::unordered_map<std::string, std::shared_ptr<Texture>> texture_cache_;

};


#endif TEXTURE_MANAGER_H_