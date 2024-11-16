//==================================================
// [ImGuiManager.h] ImGui���������߂̃w�b�_�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����FGUI���g����悤�ɂ���w�b�_�@�J���̂Ƃ������g��
//==================================================
#pragma once
#define IMGUI_DEBUG	// ImGui���g���Ƃ��̓R�����g�A�E�g���O���Ƃ�����
#ifdef IMGUI_DEBUG
#include "ImGui/imgui_impl_dx11.h"	// �ǉ�����ImGui�t�H���_����  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "StdAfx.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
/*----- �O���錾 -----*/
class ImGuiBase;
class ObjectStatesGUI;
/*--ImGui�̃}�l�[�W���[--*/
class ImGuiManager
{
public:
	static ImGuiManager* staticPointer;

	void ImGuiWin32Init(HWND _hWnd);
	void ImGuiD3D11Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);		// �Q�[�����[�v�̂͂��߂ɍs���X�V����
	void ImGuiInit();		// ������
	void ImGuiUpdate();		
	void ImGuiShowWindow();	// �E�B���h�E��\��
	void ImGuiRender();		// �`��
	void ImGuiUnInit();		// �I��
private:
	ImVector<ImGuiBase*> imGuiWindowVec;	// �E�B���h�E��S�Ă����ŊǗ�
	//ImVector<std::unique_ptr<ImGuiBase>> imGuiWindowVec;	// �X�}�|���o�����Ă��܂�
};
/*--ImGui�̊�{�I���������������N���X--*/
class ImGuiBase
{
public:
	ImGuiBase() : position_(ImVec2(0.0f, 0.0f)), showFg(true) {};
	virtual ~ImGuiBase() = default;
	virtual void SaveFile() {};	// ���͂����f�[�^��ۑ�
	virtual void LoadFile() {};	// �t�@�C����ǂ݂���
	virtual void ShowWindow() = 0;	// �E�B���h�E��\��
protected:
	ImVec2 position_ = {0.0f, 0.0f};	// �E�B���h�E�̍��W
	bool showFg = true;		// �E�B���h�E��\�����邩�ǂ���
};
/*--Unity�̃C���X�y�N�^�[�݂����Ȃ��--*/
class ObjectStatesGUI : public ImGuiBase
{
public:
	ObjectStatesGUI() : ImGuiBase() {};
	~ObjectStatesGUI() = default;
	void ShowWindow() override;
private:
	DirectX::SimpleMath::Vector3 position_ = { 2.0f, 8.0f, 0.0f };	// �l�i�[�p�ϐ�
	DirectX::SimpleMath::Vector3 rotation_ = { 0.0f, 0.0f, 0.0f };
	DirectX::SimpleMath::Vector3 scale_ = { 0.0f, 0.0f, 0.0f };
};
///*--���s���x�Ƃ������̏���\������E�B���h�E--*/
//class SyStemStatesGUI : public ImGuiBase
//{
//public:
//	SyStemStatesGUI() : ImGuiBase() {};
//	~SyStemStatesGUI() = default;
//	void ShowWindow() override;
//private:
//};
#endif // IMGUI_DEBUG