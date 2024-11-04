//==================================================
// [StdAfx.h] Standard Application Framework Extensionsヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：つまりインクルードする場所
//==================================================

#ifndef STDAFX_H_
#define STDAFX_H_

#undef UNICODE


#define _CRT_SECURE_NO_WARNINGS

/*----- インクルード -----*/
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>
#include <locale.h>
#include <string>
#include <cstdint>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>


#pragma warning(push)
#pragma warning(disable:4005)

#pragma warning(pop)

#pragma comment (lib,"winmm.lib")

constexpr uint32_t SCREEN_WIDTH = 1280;
constexpr uint32_t SCREEN_HEIGHT = 720;


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/


#endif	// STDAFX_H_
//==================================================
//				End of FIle
//==================================================
