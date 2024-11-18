//==================================================
// [main.cpp] ���C�����W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ƂĂ����C��
//==================================================

/*----- �C���N���[�h -----*/
#include <crtdbg.h>
#include <cstdint>
#include <memory>

#include "main.h"
#include "GameProcess.h"

//--------------------------------------------------
// �G���g���|�C���g
//--------------------------------------------------
int main(void)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif	// DEBUG || _DEBUG

	constexpr uint32_t SCREEN_WIDTH = 1280;
	constexpr uint32_t SCREEN_HEIGHT = 720;


	// �A�v���P�[�V�������s
	GameProcess gp(SCREEN_WIDTH, SCREEN_HEIGHT);
	gp.StartUp();
	gp.Run();
	gp.ShutDown();

	return 0;
}
