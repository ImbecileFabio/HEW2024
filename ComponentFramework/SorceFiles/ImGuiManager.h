
//==================================================
// [ImGuiManager.h] ImGui���������߂̃w�b�_�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����FGUI���g����悤�ɂ���w�b�_�@�J���̂Ƃ������g��
//==================================================
#pragma once
//#define IMGUI_DEBUG	// ImGui���g���Ƃ��̓R�����g�A�E�g���O���Ƃ�����
#ifdef IMGUI_DEBUG
#include <stack>
#include "ImGui/imgui_impl_dx11.h"	// �ǉ�����ImGui�t�H���_����  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "GameManager.h"
#include "GameObjects/GameObject.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
/*----- �O���錾 -----*/
class ImGuiBase;
class ObjectStatesGUI;
class SystemGUI;
class TreeGUI;	// TODO ������Ƃ��낻�땪����t�@�C����
/*--ImGui�̊�{�I���������������N���X--*/
class ImGuiBase
{
public:
	static std::vector<GameObject*>* objectList_;	// �E�B���h�E�ɕ\������I�u�W�F�N�g�̃��X�g
	static GameObject* selectObject_;

	ImGuiBase();
	virtual ~ImGuiBase() = default;
	virtual void SaveFile() {};	// ���͂����f�[�^��ۑ�
	virtual void LoadFile() {};	// �t�@�C����ǂ݂���
	virtual void ShowWindow() = 0;	// �E�B���h�E��\��

protected:
	ImVec2 position_ = { 0.0f, 0.0f };	// �E�B���h�E�̍��W
	bool showFg = true;		// �E�B���h�E��\�����邩�ǂ���
};

/*--ImGui�̃}�l�[�W���[--*/
class ImGuiManager
{
public:
	static ImGuiManager* staticPointer;

	void ImGuiWin32Initialize(HWND _hWnd);
	void ImGuiD3D11Initialize(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);		// �Q�[�����[�v�̂͂��߂ɍs���X�V����
	void ImGuiInitialize();		// ������
	void ImGuiUpdate();
	void ImGuiShowWindow();	// �l��G�肽�����X�g�̎Q�Ƃ������Ă���
	void ImGuiRender();		// �`��
	void ImGuiUnInitialize();		// �I��

	void ResetSelectObject() { ImGuiBase::selectObject_ = nullptr; }	// �I���I�u�W�F�N�g�����Z�b�g
	void SetObjectList(std::vector<GameObject*>& _objectList) { ImGuiBase::objectList_ = &_objectList; }	// �I�u�W�F�N�g���X�g���Z�b�g
	std::vector<ImGuiBase*> GetImGuiWindowList() { return imGuiWindowList_; }	// �E�B���h�E���X�g���擾
private:
	bool showFg = true;    // �E�B���h�E���ז��Ȏ��͂����FALSE��

	std::vector<ImGuiBase*> imGuiWindowList_;	// �E�B���h�E��S�Ă����ŊǗ�
};

/*--Unity�̃C���X�y�N�^�[�݂����Ȃ��--*/
class ObjectStatesGUI : public ImGuiBase
{
public:
	ObjectStatesGUI() : ImGuiBase() {};
	~ObjectStatesGUI() = default;
	void ShowWindow() override;

private:
	DirectX::SimpleMath::Vector3 position_ = { 0.0f, 0.0f, 0.0f };	// �l�i�[�p�ϐ�
	DirectX::SimpleMath::Vector3 rotation_ = { 0.0f, 0.0f, 0.0f };
	DirectX::SimpleMath::Vector3 scale_ = { 0.0f, 0.0f, 0.0f };
};
/*--���s���x�Ƃ������̏���\������E�B���h�E--*/
class SystemGUI : public ImGuiBase
{
public:
	SystemGUI() : ImGuiBase() {};
	~SystemGUI() = default;
	void ShowWindow() override;
private:
};
/*--Object��Component��e�q�`���ŕ\������c���[�`���E�B���h�E--*/
class TreeGUI : public ImGuiBase
{
public:
	TreeGUI() : ImGuiBase() {};
	~TreeGUI() = default;
	void ShowWindow() override;
private:
};
#endif // IMGUI_DEBUG