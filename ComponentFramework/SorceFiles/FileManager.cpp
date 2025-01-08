#include "FileManager.h"
#include <fstream>
#include <iostream>
//--------------------------------------------------
// ファイルにデータを保存する関数
//--------------------------------------------------
bool FileManager::SaveFile(const std::string& _fileName, const std::string& _data)
{
    std::cout << std::format("＜FileManager＞ -> SaveFile\n");
    std::ofstream outFile(_fileName, std::ios::out | std::ios::trunc);
    if (!IsFileStreamValid(outFile))
    {
        std::cout << std::format("＜FileManager＞ -> Error!\n");
        return false;
    }

	outFile << _data;   // データを書き込む
    outFile.close();
    return true;
}
//--------------------------------------------------
// ファイルからデータを読み込む関数
//--------------------------------------------------
bool FileManager::LoadFile(const std::string& _fileName, std::vector<std::string>& _data)
{
    std::cout << std::format("＜FileManager＞ -> LoadFile\n");
    std::ifstream inFile(_fileName, std::ios::in);
	if (!IsFileStreamValid(inFile)) // ファイルが開けなかった場合
    {
        std::cout << std::format("＜FileManager＞ -> LoadFile -> Error!\n");
        return false;
    }

    std::string line;
	while (std::getline(inFile, line))  // 1行ずつ読み込む
    {
        std::cout << std::format("＜FileManager＞ -> LoadFile -> push_back\n");
		_data.push_back(line);  // 追加
    }

    inFile.close();
    return true;
}
//--------------------------------------------------
// ファイルがあるかどうか確認する関数
//--------------------------------------------------
bool FileManager::FileExists(const std::string& _fileName)
{
    std::cout << std::format("＜FileManager＞ -> FileExists\n");
    std::ifstream file(_fileName);
    return file.good();
}
//--------------------------------------------------
// ファイルのサイズを取得する関数
//--------------------------------------------------
size_t FileManager::GetFileSize(const std::string& _fileName)
{
    std::cout << std::format("＜FileManager＞ -> GetFileSize\n");
    std::ifstream file(_fileName, std::ios::binary | std::ios::ate);
	if (!file)  // ファイルが開けなかった場合
    {
        std::cout << std::format("＜FileManager＞ -> GetFileSize -> Error!\n");
        return 0;
    }

	return static_cast<size_t>(file.tellg());   // ファイルサイズを取得
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
FileManager::~FileManager()
{
}
//--------------------------------------------------
// ストリームが成功したかどうかを確認するヘルパー関数
//--------------------------------------------------
bool FileManager::IsFileStreamValid(const std::ifstream& _ifstream)
{
    return _ifstream.is_open() && _ifstream.good();
}
//--------------------------------------------------
// ストリームが成功したかどうかを確認するヘルパー関数
//--------------------------------------------------
bool FileManager::IsFileStreamValid(const std::ofstream& _ofstream)
{
    return _ofstream.is_open() && _ofstream.good();

}
