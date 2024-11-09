//==================================================
// [GameProcess.h] ゲーム実行処理モジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームの実行部分をまとめたクラスらしい
//		 ウィンドウの作成も兼ねてます
//==================================================
#ifndef GAME_PROCESS_H_
#define GAME_PROCESS_H_

/*----- インクルード -----*/
#include "StdAfx.h"
/*----- 構造体定義 -----*/


/*----- 前方宣言 -----*/
class GameManager;

//--------------------------------------------------
// ゲームプロセスクラス
//--------------------------------------------------
class GameProcess
{
public:
	GameProcess(uint32_t width, uint32_t height);
	~GameProcess(void);

	bool StartUp(void);
	void Run(void);
	void ShutDown(void);

	// ウィンドウの幅と高さを返す
	static uint32_t GetWidth() { return width_; }
	static uint32_t GetHeight() { return height_; }
	
	// ウィンドウハンドルを返す
	static HWND GetWindowHandle(){ return hWnd_; }

private:

	bool Init(void);
	void Uninit(void);
	bool InitWnd(void);
	void UninitWnd(void);
	void Update(void);
	void GenerateOutput(void);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

	static HINSTANCE hInst_;	// アプリケーションインスタンスハンドル
	static HWND		 hWnd_;		// ウィンドウハンドル
	static uint32_t	 width_;	// ウィンドウの横幅
	static uint32_t	 height_;	// ウィンドウの縦幅

	GameManager* game_manager_{};	// ゲーム管理インスタンス
};

#endif // GAME_PROCESS_H_
