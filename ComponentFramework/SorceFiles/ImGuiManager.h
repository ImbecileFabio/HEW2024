//==================================================
// [ImGuiManager.h] ImGuiを扱うためのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：GUIを使えるようにするヘッダ　開発のときだけ使う
//==================================================
#pragma once
#define IMGUI_DEBUG	// ImGuiを使うときはコメントアウトを外すといける
#ifdef IMGUI_DEBUG
#include "ImGui/imgui_impl_dx11.h"	// 追加したImGuiフォルダから  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "StdAfx.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
/*----- 前方宣言 -----*/
class ImGuiBase;
class ObjectStatesGUI;
/*--ImGuiのマネージャー--*/
class ImGuiManager
{
public:
	static ImGuiManager* staticPointer;

	void ImGuiWin32Init(HWND _hWnd);
	void ImGuiD3D11Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);		// ゲームループのはじめに行う更新処理
	void ImGuiInit();		// 初期化
	void ImGuiUpdate();		
	void ImGuiShowWindow();	// ウィンドウを表示
	void ImGuiRender();		// 描画
	void ImGuiUnInit();		// 終了
private:
	ImVector<ImGuiBase*> imGuiWindowVec;	// ウィンドウを全てここで管理
	//ImVector<std::unique_ptr<ImGuiBase>> imGuiWindowVec;	// スマポを出直してきます
};
/*--ImGuiの基本的処理を書いた基底クラス--*/
class ImGuiBase
{
public:
	ImGuiBase() : position_(ImVec2(0.0f, 0.0f)), showFg(true) {};
	virtual ~ImGuiBase() = default;
	virtual void SaveFile() {};	// 入力したデータを保存
	virtual void LoadFile() {};	// ファイルを読みこむ
	virtual void ShowWindow() = 0;	// ウィンドウを表示
protected:
	ImVec2 position_ = {0.0f, 0.0f};	// ウィンドウの座標
	bool showFg = true;		// ウィンドウを表示するかどうか
};
/*--Unityのインスペクターみたいなやつ--*/
class ObjectStatesGUI : public ImGuiBase
{
public:
	ObjectStatesGUI() : ImGuiBase() {};
	~ObjectStatesGUI() = default;
	void ShowWindow() override;
private:
	DirectX::SimpleMath::Vector3 position_ = { 2.0f, 8.0f, 0.0f };	// 値格納用変数
	DirectX::SimpleMath::Vector3 rotation_ = { 0.0f, 0.0f, 0.0f };
	DirectX::SimpleMath::Vector3 scale_ = { 0.0f, 0.0f, 0.0f };
};
///*--実行速度とか内部の情報を表示するウィンドウ--*/
//class SyStemStatesGUI : public ImGuiBase
//{
//public:
//	SyStemStatesGUI() : ImGuiBase() {};
//	~SyStemStatesGUI() = default;
//	void ShowWindow() override;
//private:
//};
#endif // IMGUI_DEBUG