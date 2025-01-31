
//==================================================
// [ImGuiManager.h] ImGuiを扱うためのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：GUIを使えるようにするヘッダ　開発のときだけ使う
//==================================================
#pragma once
//#define IMGUI_DEBUG	// ImGuiを使うときはコメントアウトを外すといける
#ifdef IMGUI_DEBUG
#include <stack>
#include "ImGui/imgui_impl_dx11.h"	// 追加したImGuiフォルダから  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "GameManager.h"
#include "GameObjects/GameObject.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
/*----- 前方宣言 -----*/
class ImGuiBase;
class ObjectStatesGUI;
class SystemGUI;
class TreeGUI;	// TODO ちょっとそろそろ分けるファイルを
/*--ImGuiの基本的処理を書いた基底クラス--*/
class ImGuiBase
{
public:
	static std::vector<GameObject*>* objectList_;	// ウィンドウに表示するオブジェクトのリスト
	static GameObject* selectObject_;

	ImGuiBase();
	virtual ~ImGuiBase() = default;
	virtual void SaveFile() {};	// 入力したデータを保存
	virtual void LoadFile() {};	// ファイルを読みこむ
	virtual void ShowWindow() = 0;	// ウィンドウを表示

protected:
	ImVec2 position_ = { 0.0f, 0.0f };	// ウィンドウの座標
	bool showFg = true;		// ウィンドウを表示するかどうか
};

/*--ImGuiのマネージャー--*/
class ImGuiManager
{
public:
	static ImGuiManager* staticPointer;

	void ImGuiWin32Initialize(HWND _hWnd);
	void ImGuiD3D11Initialize(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);		// ゲームループのはじめに行う更新処理
	void ImGuiInitialize();		// 初期化
	void ImGuiUpdate();
	void ImGuiShowWindow();	// 値を触りたいリストの参照を持ってくる
	void ImGuiRender();		// 描画
	void ImGuiUnInitialize();		// 終了

	void ResetSelectObject() { ImGuiBase::selectObject_ = nullptr; }	// 選択オブジェクトをリセット
	void SetObjectList(std::vector<GameObject*>& _objectList) { ImGuiBase::objectList_ = &_objectList; }	// オブジェクトリストをセット
	std::vector<ImGuiBase*> GetImGuiWindowList() { return imGuiWindowList_; }	// ウィンドウリストを取得
private:
	bool showFg = true;    // ウィンドウが邪魔な時はこれをFALSEに

	std::vector<ImGuiBase*> imGuiWindowList_;	// ウィンドウを全てここで管理
};

/*--Unityのインスペクターみたいなやつ--*/
class ObjectStatesGUI : public ImGuiBase
{
public:
	ObjectStatesGUI() : ImGuiBase() {};
	~ObjectStatesGUI() = default;
	void ShowWindow() override;

private:
	DirectX::SimpleMath::Vector3 position_ = { 0.0f, 0.0f, 0.0f };	// 値格納用変数
	DirectX::SimpleMath::Vector3 rotation_ = { 0.0f, 0.0f, 0.0f };
	DirectX::SimpleMath::Vector3 scale_ = { 0.0f, 0.0f, 0.0f };
};
/*--実行速度とか内部の情報を表示するウィンドウ--*/
class SystemGUI : public ImGuiBase
{
public:
	SystemGUI() : ImGuiBase() {};
	~SystemGUI() = default;
	void ShowWindow() override;
private:
};
/*--ObjectとComponentを親子形式で表示するツリー形式ウィンドウ--*/
class TreeGUI : public ImGuiBase
{
public:
	TreeGUI() : ImGuiBase() {};
	~TreeGUI() = default;
	void ShowWindow() override;
private:
};
#endif // IMGUI_DEBUG