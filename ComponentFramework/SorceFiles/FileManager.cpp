#include "FileManager.h"
#include <fstream>
#include <iostream>
//--------------------------------------------------
// �t�@�C���Ƀf�[�^��ۑ�����֐�
//--------------------------------------------------
bool FileManager::SaveFile(const std::string& _fileName, const std::string& _data)
{
    std::cout << std::format("��FileManager�� -> SaveFile\n");
    std::ofstream outFile(_fileName, std::ios::out | std::ios::trunc);
    if (!IsFileStreamValid(outFile))
    {
        std::cout << std::format("��FileManager�� -> Error!\n");
        return false;
    }

	outFile << _data;   // �f�[�^����������
    outFile.close();
    return true;
}
//--------------------------------------------------
// �t�@�C������f�[�^��ǂݍ��ފ֐�
//--------------------------------------------------
bool FileManager::LoadFile(const std::string& _fileName, std::vector<std::string>& _data)
{
    std::cout << std::format("��FileManager�� -> LoadFile\n");
    std::ifstream inFile(_fileName, std::ios::in);
	if (!IsFileStreamValid(inFile)) // �t�@�C�����J���Ȃ������ꍇ
    {
        std::cout << std::format("��FileManager�� -> LoadFile -> Error!\n");
        return false;
    }

    std::string line;
	while (std::getline(inFile, line))  // 1�s���ǂݍ���
    {
        std::cout << std::format("��FileManager�� -> LoadFile -> push_back\n");
		_data.push_back(line);  // �ǉ�
    }

    inFile.close();
    return true;
}
//--------------------------------------------------
// �t�@�C�������邩�ǂ����m�F����֐�
//--------------------------------------------------
bool FileManager::FileExists(const std::string& _fileName)
{
    std::cout << std::format("��FileManager�� -> FileExists\n");
    std::ifstream file(_fileName);
    return file.good();
}
//--------------------------------------------------
// �t�@�C���̃T�C�Y���擾����֐�
//--------------------------------------------------
size_t FileManager::GetFileSize(const std::string& _fileName)
{
    std::cout << std::format("��FileManager�� -> GetFileSize\n");
    std::ifstream file(_fileName, std::ios::binary | std::ios::ate);
	if (!file)  // �t�@�C�����J���Ȃ������ꍇ
    {
        std::cout << std::format("��FileManager�� -> GetFileSize -> Error!\n");
        return 0;
    }

	return static_cast<size_t>(file.tellg());   // �t�@�C���T�C�Y���擾
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
FileManager::~FileManager()
{
}
//--------------------------------------------------
// �X�g���[���������������ǂ������m�F����w���p�[�֐�
//--------------------------------------------------
bool FileManager::IsFileStreamValid(const std::ifstream& _ifstream)
{
    return _ifstream.is_open() && _ifstream.good();
}
//--------------------------------------------------
// �X�g���[���������������ǂ������m�F����w���p�[�֐�
//--------------------------------------------------
bool FileManager::IsFileStreamValid(const std::ofstream& _ofstream)
{
    return _ofstream.is_open() && _ofstream.good();

}
