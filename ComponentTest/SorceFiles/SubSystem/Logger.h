//==================================================
// [Logger.h] �f�o�b�O���O���W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�f�o�b�O�p�ɃR���\�[���E�B���h�E��\�������肷��
//==================================================
#ifndef CREATE_CONSOLE_H
#define CREATE_CONSOLE_H

/*----- �C���N���[�h -----*/
#include "../StdAfx.h"

/*----- �\���̒�` -----*/
enum class LogLevel
{
	Info
	,Warn
	,Error
};

/*----- �O���錾 -----*/

//--------------------------------------------------
// �f�o�b�O�N���X
//--------------------------------------------------
class Logger
{
public:
	static void Log(const std::string& message, LogLevel = LogLevel::Info);
	static void Initialize();
	static void Sutdown();

};


#endif	// CREATE_CONSOLE_H
//==================================================
//				End of FIle
//==================================================

