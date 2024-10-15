//==================================================
// [main.cpp] メインモジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とてもメイン
//==================================================


#undef UNICODE

/*----- インクルード -----*/
#include "StdAfx.h"
#include "GameProcess.h"
#include "Direct3D.h"
#include "SubSystem/Logger.h"

/*----- WindowProc 関数プロトタイプ -----*/
LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);


//--------------------------------------------------
// Windows プログラムのエントリーポイント
//--------------------------------------------------
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WindowClass1";

    // register the window class
    RegisterClassEx(&wc);

    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // set the size, but not the position
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(
        NULL,
        "WindowClass1",    // name of the window class
        WINDOW_NAME,   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        600,    // x-position of the window
        75,    // y-position of the window
        wr.right - wr.left,    // width of the window
        wr.bottom - wr.top,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        hInstance,    // application handle
        NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);

    //--------------------------------------------------
    // ゲーム初期化
    //--------------------------------------------------
    // ログ出力用
    Logger logger;
    Logger::Initialize();
    // ゲームプロセス生成
    std::cout << "[ゲームプロセス] -> 生成\n";
    GameProcess gameProcess(&hWnd);
    gameProcess.StartUp();


    // this struct holds Windows event messages
    MSG msg = { 0 };

    // FPS固定用
    LARGE_INTEGER liWork;
    long long frequency;    //カウントする時間の細かさ
    QueryPerformanceFrequency(&liWork);
    frequency = liWork.QuadPart;
    long long oldCount = liWork.QuadPart;   // 前回計測時の時間
    long long nowCount = oldCount;          // 今回計測時の時間

    //--------------------------------------------------
    // ゲームループ
    //--------------------------------------------------
    while (TRUE)
    {
         std::cout << "================[ゲームループ開始]================\n";
        // キューに待機中のメッセージがないか確認
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            // キーストローク メッセージを適切な形式に変換
            TranslateMessage(&msg);

            // メッセージを WindowProc 関数に送信
            DispatchMessage(&msg);

            // 終了するタイミングかどうか確認
            if (msg.message == WM_QUIT) { break; }
        }
        else {
            //--------------------------------------------------
            // ゲームのコード
            //--------------------------------------------------
            QueryPerformanceCounter(&liWork);   // 現在時間を取得
            nowCount = liWork.QuadPart;
            // 1/30が経過したか？
            if (nowCount = oldCount + frequency / 30) {
                //--------------------------------------------------
                // ゲーム処理実行
                //--------------------------------------------------
                gameProcess.Run();
            }
        }
    }
    std::cout << "================[ゲームループ終了]================\n";
    //--------------------------------------------------
    // ゲーム終了
    //--------------------------------------------------
    gameProcess.ShutDown();
    logger.Sutdown();

    UnregisterClass("WindowClass1", hInstance);

    // return this part of the WM_QUIT message to Windows
    return (int)msg.wParam;
}

//--------------------------------------------------
// ウィンドウプロシージャ
//--------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
    //このメッセージの時はウィンドウを破棄する
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    } break;

    // 「x」ボタンが押されたら
    case WM_CLOSE: 
    {
        int res = MessageBoxA(NULL, "おわる？", "かくにん", MB_OKCANCEL);
        if (res == IDOK)
        {
            DestroyWindow(hWnd);  // 「WM_DESTROY」メッセージを送る
        }
    }
    case WM_KEYDOWN: //キー入力があったメッセージ
        if (LOWORD(wParam) == VK_ESCAPE) { //入力されたキーがESCAPEなら
            PostMessage(hWnd, WM_CLOSE, wParam, lParam);//「WM_CLOSE」を送る
        }
    }

    // 受け取ったメッセージに対してデフォルトの処理を実行
    return DefWindowProc(hWnd, message, wParam, lParam);
}


