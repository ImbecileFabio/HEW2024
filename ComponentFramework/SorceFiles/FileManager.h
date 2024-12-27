//==================================================
// [FileManager.h] �t�@�C���������Ǘ�����}�l�[�W���[
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����E�Ǎ��������Ǘ�����}�l�[�W���[�N���X
//==================================================
#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

/*----- �C���N���[�h -----*/
#include <string>
#include <vector>
//-----------------------------------------------------------------
// �t�@�C���}�l�[�W���[�N���X
//-----------------------------------------------------------------
class FileManager
{
public:
	// �V���O���g���Ȃ���̂��R�s�y
	static FileManager& GetInstance()
	{
		static FileManager instance;
		return instance;
	}
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;

	// �t�@�C���ۑ�
	bool SaveFile(const std::string& _fileName, const std::string& _data);
	// �t�@�C���Ǎ�
	bool LoadFile(const std::string& _fileName, std::vector<std::string>& _data);
	// �t�@�C���̑��݊m�F
	bool FileExists(const std::string& _fileName);
	// �t�@�C���̃T�C�Y���擾
	size_t GetFileSize(const std::string& _fileName);
private:
	FileManager(); //�R���X�g���N�^
	~FileManager(); //�f�X�g���N�^
	// �����w���p�[�֐��i��: �t�@�C���X�g���[���G���[�`�F�b�N�j
	bool IsFileStreamValid(const std::ifstream& _ifstream);
	bool IsFileStreamValid(const std::ofstream& _ofstream);
};

#endif // _FILE_MANAGER_H_