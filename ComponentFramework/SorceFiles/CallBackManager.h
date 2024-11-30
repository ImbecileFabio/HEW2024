//=================================================================
// [CallBackManager.h] コールバックマネージャーモジュールヘッダ
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：コールバックで呼びだすイベント当の管理を行うクラス
//=================================================================
#ifndef CALLBACK_MANAGER_H_
#define CALLBACK_MANAGER_H_
/*----- インクルード -----*/
#include<memory>
#include<vector>
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//-----------------------------------------------------------------
// コールバックーマネージャークラス
//-----------------------------------------------------------------
class CallBackManager
{
public:
	CallBackManager(void);
	~CallBackManager(void);
	// インスタンス生成
	static auto Create(void) { return new CallBackManager(); }
	void InitAll(void);
	void UninitAll(void);
	void UpdateAll(void);
private:
};
#endif // CALLBACK_MANAGER_H_