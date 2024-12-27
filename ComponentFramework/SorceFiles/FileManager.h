//==================================================
// [FileManager.h] ファイル処理を管理するマネージャー
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：書込・読込処理を管理するマネージャークラス
//==================================================
#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_

/*----- インクルード -----*/
#include <string>
#include <vector>
//-----------------------------------------------------------------
// ファイルマネージャークラス
//-----------------------------------------------------------------
class FileManager
{
public:
	// シングルトンなるものをコピペ
	static FileManager& GetInstance()
	{
		static FileManager instance;
		return instance;
	}
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;

	// ファイル保存
	bool SaveFile(const std::string& _fileName, const std::string& _data);
	// ファイル読込
	bool LoadFile(const std::string& _fileName, std::vector<std::string>& _data);
	// ファイルの存在確認
	bool FileExists(const std::string& _fileName);
	// ファイルのサイズを取得
	size_t GetFileSize(const std::string& _fileName);
private:
	FileManager(); //コンストラクタ
	~FileManager(); //デストラクタ
	// 内部ヘルパー関数（例: ファイルストリームエラーチェック）
	bool IsFileStreamValid(const std::ifstream& _ifstream);
	bool IsFileStreamValid(const std::ofstream& _ofstream);
};

#endif // _FILE_MANAGER_H_