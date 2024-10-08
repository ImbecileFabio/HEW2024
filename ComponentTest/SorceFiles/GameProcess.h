//==================================================
// [GameProcess.h] ゲーム実行処理モジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームの実行部分をまとめたクラスらしい
//==================================================
#ifndef GAME_PROCESS_H_
#define GAME_PROCESS_H_

/*----- インクルード -----*/

/*----- 構造体定義 -----*/


/*----- 前方宣言 -----*/


//--------------------------------------------------
// ゲームプロセスクラス
//--------------------------------------------------
class GameProcess
{
public:
	GameProcess(HWND* hWnd);
	~GameProcess(void);

public:
	bool StartUp(void);
	void Run(void);
	void ShutDown(void);

private:
	bool Init(void);
	void Uninit(void);
	void ProcessInput(void);
	void Update(float deltaTime);
	void GenerateOutput(void);

private:
	class GameManager* game_manager_;
	HWND* hWnd_;
};

#endif // GAME_PROCESS_H_
//==================================================
//				End of FIle
//==================================================
