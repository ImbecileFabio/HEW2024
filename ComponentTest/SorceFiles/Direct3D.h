//==================================================
// [Direct3D.h] �����_���[���W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����FDirect3D�̏o�͏����������܂Ƃ߂��N���X
//==================================================
#ifndef DIRECT3D_H_
#define DIRECT3D_H_

/*----- �}�N���̒�` -----*/
#define SCREEN_WIDTH (800)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (800)	// �E�C���h�E�̍���
#define WINDOW_NAME ("Mitana")	// �E�B���h�E�ɕ\������閼�O


/*----- �C���N���[�h -----*/
#include "StdAfx.h"
#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h>// DirectX�̐��w�֐��֘A�̃w�b�_�[�t�@�C��
#include <cstdlib>




/*----- �\���̒�` -----*/
// ���_�f�[�^��\���\����
struct Vertex
{
	// ���_�̈ʒu���W
	float x, y, z;
	// �F���
	float r, g, b, a;
	// �e�N�X�`�����W�iUV���W�j
	float u, v;
};

// �萔�o�b�t�@�p�\����
struct ConstBuffer
{
	// ���_�J���[�s��
	DirectX::XMFLOAT4 color;
	// UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;
	// �v���W�F�N�V�����ϊ��s��
	DirectX::XMMATRIX matrixProj;
	// ���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;
};

// �����̒�`
enum class DIRECTION
{
	Up
	, Right
	, Left
	, Down
};

/*----- �O���錾 -----*/

//--------------------------------------------------
// �����_���[�̏o�͏����N���X
//--------------------------------------------------
class Direct3D
{
public:
	Direct3D(class GameManager* gameManager);
	~Direct3D();

	HRESULT WindowCreate(HWND* hWnd);
	void Release();
	void Draw();
	void StartRender();
	void FinishRender();

	void AddSprite(class SpriteComponent* spriteComponent);
	void RemoveSprite(class SpriteComponent* SpriteComponent);

private:
	std::vector<class SpriteComponent*> sprites_;
};


/*----- �G�N�X�^�[�� -----*/
extern ComPtr<ID3D11Device> g_cpDevice; // �f�o�C�X��DirectX�̊e��@�\�����
extern ComPtr<ID3D11DeviceContext> g_cpDeviceContext;// �R���e�L�X�g���`��֘A���i��@�\
extern ComPtr<ID3D11Buffer> g_cpConstantBuffer;


#endif	// DIRECT3D_H_
//==================================================
//				End of FIle
//==================================================
