//==================================================
// [ImGuiManager.h] ImGuiを扱うためのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：GUIを使えるようにするヘッダ　開発のときだけ使う
//==================================================
#pragma once
#define IMGUI_MANAGER_H_	// ImGuiを使うときはコメントアウトを外すといける
#ifdef IMGUI_MANAGER_H_
#include "ImGui/imgui_impl_dx11.h"	// 追加したImGuiフォルダから  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "Renderer.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
/*--ImGuiの機能を関数の中に入れたクラス--*/
class ImGuiManager
{
public:
	void ImGuiWin32Init(HWND _hWnd);
	void ImGuiD3D11Init();
	void ImGuiUpdate();		// ゲームループのはじめに行う更新処理
	void ImGuiShowWindow();	// ウィンドウを表示
	void ImGuiRender();		// 描画
	void ImGuiUnInit();		// 終了
private:
	Renderer* renderer_ = nullptr;	// ID3D11DeviceとID3D11DeviceContextがほしいため

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	DirectX::SimpleMath::Vector3 position_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 scale_	   = {0.0f, 0.0f, 0.0f};

	bool showWindowObject = true;	// ウィンドウを表示するかどうか
};

#endif // IMGUI_MANAGER_H_
