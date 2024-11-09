//==================================================
// [ImGuiManager.h] ImGuiを扱うためのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：GUIを使えるようにするヘッダ　開発のときだけ使う
//==================================================
#pragma once
#define DEBUG	// デバッグモード ちゃんと整備して書きます
#ifdef DEBUG	// デバッグモードのときのみヘッダを読込
#include <wrl/client.h>				// ComPtr コンポタ
#include "ImGui/imgui_impl_dx11.h"	// 追加したImGuiフォルダから  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "Renderer.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
#endif
/*--ImGuiの機能を関数の中に入れたクラス--*/
class ImGuiApp
{
public:
	void ImGuiWin32Init();
	void ImGuiD3D11Init();
	void ImGuiUpdate();		// ゲームループのはじめに行う更新処理
	void ImGuiShowWindow();	// ウィンドウを表示
	void ImGuiRender();		// 描画
	void ImGuiUnInit();		// 終了
	// セッター関数
	void SetPosition(DirectX::SimpleMath::Vector3 _position) { position_ = _position; }
	void SetRotation(DirectX::SimpleMath::Vector3 _rotation) { rotation_ = _rotation; }
	void SetScale	(DirectX::SimpleMath::Vector3 _scale) { scale_ = _scale; }
private:
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	DirectX::SimpleMath::Vector3 position_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 scale_	   = {0.0f, 0.0f, 0.0f};

	HWND hWnd_;													// ImGuiのウィンドウハンドル
	Microsoft::WRL::ComPtr<ID3D11Device>			   device_;	// ImGuiで使うDirectX11デバイス
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext_;	// ImGuiで使うDirectX11コンテキスト
	// フラグ変数　あとで消す
	bool showWindow = true;			// ImGuiのウィンドウ状態
	bool showWindowAnother = false;	// もう一個別のウィンドウ
	bool showWindowObject = true;	// オブジェクトの情報を表示するウィンドウ
};

