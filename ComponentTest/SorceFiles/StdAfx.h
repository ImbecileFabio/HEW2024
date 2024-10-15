//==================================================
// [StdAfx.h] Standard Application Framework Extensionsヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：つまりインクルードする場所
//==================================================
#ifndef STDAFX_H_
#define STDAFX_H_

#undef UNICODE

// デバッグ時以外はコメントアウト
#define DEBUG_


/*----- インクルード -----*/
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>
#include <wrl/client.h>	// ComPtr用

/*----- 名前空間 -----*/
using Microsoft::WRL::ComPtr;

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/


#endif	// STDAFX_H_
//==================================================
//				End of FIle
//==================================================
